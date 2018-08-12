#include "machine.h"
#include <iostream>
#include <boost/format.hpp>
#include "endianess.h"
#include "hardwareinterrupt.h"

uint32_t puck::Machine::register_set::Register::getUInt32() const {
    return getUInt32BigEndian(bytes);
}

void puck::Machine::register_set::Register::storeUInt32(const uint32_t value) {
    storeUInt32BigEndian(bytes, value);
}

int32_t puck::Machine::register_set::Register::getInt32() const {
    return getInt32BigEndian(bytes);
}

void puck::Machine::register_set::Register::storeInt32(const int32_t value) {
    storeInt32BigEndian(bytes, value);
}

int8_t puck::Machine::register_set::Register::getUInt8() const {
    return bytes[LSB];
}

void puck::Machine::register_set::Register::storeUInt8(const int8_t value) {
    zero();
    bytes[LSB] = value;
}

const puck::Machine::register_set::Register& puck::Machine::register_set::readRegister(const uint8_t n) const {
    if (n >= REGISTER_COUNT)
        throw InvalidRegisterAccessInterrupt(
                                             (boost::format("Accessed nonexisting register %u") % n).str().data());

    return _registers[n];
}

puck::Machine::register_set::Register& puck::Machine::register_set::writeRegister(const uint8_t n) {
    if (n >= REGISTER_COUNT)
        throw InvalidRegisterAccessInterrupt(
                                             (boost::format("Accessed nonexisting register %u") % n).str().data());
    if (n == 0) throw InvalidRegisterAccessInterrupt("Tried to open register $0 for writing");

    return _registers[n];
}

void puck::Machine::memory::checkAddress(const address_t address) const {
    if (address >= MEMORY_SIZE) throw SegfaultInterrupt((boost::format("Segfault at 0x%8X") % address).str().data());
}

void puck::Machine::memory::readByteInto(byte* dst, const address_t address) const {
    checkAddress(address);

    *dst = _memory[address];
}

void puck::Machine::memory::readHalfwordInto(byte* dst, const address_t address) const {
    checkAddress(address + 1);

    memcpy(dst, &_memory[address], 2);
}

void puck::Machine::memory::readWordInto(byte* dst, const address_t address) const {
    checkAddress(address + 3);

    memcpy(dst, &_memory[address], 4);
}

void puck::Machine::memory::storeByte(byte const* src, const address_t address) {
    if (failWhenWritingCode && address < codeSize) throw CodeOverwrittenInterrupt(address);
    checkAddress(address);

    _memory[address] = *src;
}

void puck::Machine::memory::storeHalfword(byte const* src, const address_t address) {
    if (failWhenWritingCode && address < codeSize) throw CodeOverwrittenInterrupt(address);
    checkAddress(address + 1);

    memcpy(&_memory[address], src, 2);
}

bool puck::Machine::memory::storeWord(byte const* src, const address_t address) {
    if (failWhenWritingCode && address < codeSize) throw CodeOverwrittenInterrupt(address);
    checkAddress(address + 3);

    memcpy(&_memory[address], src, 4);

    return true;
}

puck::Machine::byte& puck::Machine::memory::getByte(const address_t address) {
    checkAddress(address);

    return _memory[address];
}

puck::Machine::byte* puck::Machine::memory::getBasePointer() {
    return _memory;
}

puck::Machine::Machine(const bool failWhenWritingCode)
    : _isHalted(false),
      _pc(0) {
    _memory.failWhenWritingCode = failWhenWritingCode;
}

void puck::Machine::loadExecutable(std::ifstream& stream) {
    _memory.codeSize = readExecutable(stream, _memory.getBasePointer());
    _isHalted = false;
}

void puck::ProgramRunner::run() const {
    try {
        while (!_machine.isHalted()) _machine.executeInstruction();
        std::cerr << "VM halted by HALT instruction\n";
    } catch (HardwareInterrupt& interrupt) {
        std::cerr << "Interrupted: " << interrupt.what() << "\n";
    }
}

puck::OpCode puck::Machine::getOpCode() {
    return static_cast<OpCode>(_memory.getByte(_pc));
}

uint8_t& puck::Machine::getImmediate(const uint8_t n) {
    return _memory.getByte(_pc + 1 + n);
}

void puck::Machine::executeInstruction() {
    struct PcIncrement {
        uint32_t& pc;
        const OpCode opCode;
        const bool& jumped;

        PcIncrement(uint32_t& pc, bool& jumped, const OpCode opCode)
            : pc(pc),
              opCode(opCode),
              jumped(jumped) { }

        ~PcIncrement() {
            if (!jumped) pc += getInstructionSize(opCode);
        }
    };

    _jumped = false;
    const auto op = getOpCode();
    PcIncrement increment(_pc, _jumped, op);

    try {
        switch (op) {
            case OpCode::ADD: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        +
                                                                        _registerSet.readRegister(getImmediate(2)).getUInt32()
                                                                       );
                break;
            }
            case OpCode::SUB: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        -
                                                                        _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::MULU: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        *
                                                                        _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::DIVU: {
                const auto divisor = _registerSet.readRegister(getImmediate(2)).getUInt32();
                if (divisor == 0) throw DividedByZeroInterrupt(_pc);

                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        /
                                                                        divisor);
                break;
            }
            case OpCode::MODU: {
                const auto divisor = _registerSet.readRegister(getImmediate(2)).getUInt32();
                if (divisor == 0) throw DividedByZeroInterrupt(_pc);

                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        %
                                                                        divisor);
                break;
            }
            case OpCode::MULI: {
                _registerSet.writeRegister(getImmediate(0)).storeInt32(
                                                                       _registerSet.readRegister(getImmediate(1)).getInt32()
                                                                       *
                                                                       _registerSet.readRegister(getImmediate(2)).getInt32());
                break;
            }
            case OpCode::DIVI: {
                const auto divisor = _registerSet.readRegister(getImmediate(2)).getInt32();
                if (divisor == 0) throw DividedByZeroInterrupt(_pc);

                _registerSet.writeRegister(getImmediate(0)).storeInt32(
                                                                       _registerSet.readRegister(getImmediate(1)).getInt32()
                                                                       /
                                                                       divisor);
                break;
            }
            case OpCode::MODI: {
                const auto divisor = _registerSet.readRegister(getImmediate(2)).getInt32();
                if (divisor == 0) throw DividedByZeroInterrupt(_pc);

                _registerSet.writeRegister(getImmediate(0)).storeInt32(
                                                                       _registerSet.readRegister(getImmediate(1)).getInt32()
                                                                       %
                                                                       divisor);
                break;
            }

            case OpCode::AND: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        &
                                                                        _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::OR: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        |
                                                                        _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::XOR: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        ^
                                                                        _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::SL: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        <<
                                                                        _registerSet.readRegister(getImmediate(2)).getUInt8());
                break;
            }
            case OpCode::SR: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        >>
                                                                        _registerSet.readRegister(getImmediate(2)).getUInt8());
                break;
            }

            case OpCode::EQ: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                       ==
                                                                       _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::NE: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                       !=
                                                                       _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::LTI: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getInt32()
                                                                       <
                                                                       _registerSet.readRegister(getImmediate(2)).getInt32());
                break;
            }
            case OpCode::LEI: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getInt32()
                                                                       <=
                                                                       _registerSet.readRegister(getImmediate(2)).getInt32());
                break;
            }
            case OpCode::GTI: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getInt32()
                                                                       >
                                                                       _registerSet.readRegister(getImmediate(2)).getInt32());
                break;
            }
            case OpCode::GEI: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getInt32()
                                                                       >=
                                                                       _registerSet.readRegister(getImmediate(2)).getInt32());
                break;
            }
            case OpCode::LTU: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                       <
                                                                       _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::LEU: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                       <=
                                                                       _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::GTU: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                       >
                                                                       _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }
            case OpCode::GEU: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(
                                                                       _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                       >=
                                                                       _registerSet.readRegister(getImmediate(2)).getUInt32());
                break;
            }

            case OpCode::HALT: {
                _isHalted = true;
                break;
            }
            case OpCode::BRT: {
                if (_registerSet.readRegister(getImmediate(0)).getUInt8() != 0) jump(getUInt32BigEndian(&getImmediate(1)));
                break;
            }
            case OpCode::BRF: {
                if (_registerSet.readRegister(getImmediate(0)).getUInt8() == 0) jump(getUInt32BigEndian(&getImmediate(1)));
                break;
            }
            case OpCode::JMP: {
                jump(getUInt32BigEndian(&getImmediate(0)));
                break;
            }
            case OpCode::JMPR: {
                jump(_registerSet.readRegister(getImmediate(0)).getUInt32());
                break;
            }
            case OpCode::CALL: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(_pc + getInstructionSize(op));
                jump(getUInt32BigEndian(&getImmediate(1)));
                break;
            }
            case OpCode::CALLR: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(_pc + getInstructionSize(op));
                jump(_registerSet.readRegister(getImmediate(1)).getUInt32());
                break;
            }

            case OpCode::INC: {
                uint8_t c;
                std::cin.read(reinterpret_cast<char*>(&c), 1);
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(c);
                break;
            }
            case OpCode::OUTC: {
                std::cout << static_cast<char>(_registerSet.readRegister(getImmediate(0)).getUInt8());
                break;
            }
            case OpCode::INU: {
                uint32_t in;
                std::cin >> in;
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(in);
            }
            case OpCode::OUTU: {
                std::cout << _registerSet.readRegister(getImmediate(0)).getUInt32();
                break;
            }
            case OpCode::INI: {
                int32_t in;
                std::cin >> in;
                _registerSet.writeRegister(getImmediate(0)).storeInt32(in);
            }
            case OpCode::OUTI: {
                std::cout << _registerSet.readRegister(getImmediate(0)).getInt32();
                break;
            }
            case OpCode::INF: throw InstructionNotImplementedInterrupt("INF", OpCode::INF);
            case OpCode::OUTF: throw InstructionNotImplementedInterrupt("OUTF", OpCode::OUTF);

            case OpCode::LDB: {
                auto& reg = _registerSet.writeRegister(getImmediate(0));
                reg.zero();
                _memory.readByteInto(&reg.bytes[register_set::Register::LSB],
                                     _registerSet.readRegister(getImmediate(1)).getUInt32());
                break;
            }
            case OpCode::LDHW: {
                auto& reg = _registerSet.writeRegister(getImmediate(0));
                reg.zero();
                _memory.readHalfwordInto(&reg.bytes[register_set::Register::LSHW],
                                         _registerSet.readRegister(getImmediate(1)).getUInt32());
                break;
            }
            case OpCode::LDW: {
                auto& reg = _registerSet.writeRegister(getImmediate(0));
                _memory.readWordInto(reg.bytes,
                                     _registerSet.readRegister(getImmediate(1)).getUInt32());
                break;
            }
            case OpCode::STB: {
                _memory.storeByte(&_registerSet.readRegister(getImmediate(0)).bytes[register_set::Register::LSB],
                                  _registerSet.readRegister(getImmediate(1)).getUInt32());
                break;
            }
            case OpCode::STHW: {
                _memory.storeHalfword(&_registerSet.readRegister(getImmediate(0)).bytes[register_set::Register::LSHW],
                                      _registerSet.readRegister(getImmediate(1)).getUInt32());
                break;
            }
            case OpCode::STW: {
                const auto result = _memory.storeWord(_registerSet.readRegister(getImmediate(0)).bytes,
                                                      _registerSet.readRegister(getImmediate(1)).getUInt32());
                if (!result) {
                    std::cerr << (boost::format("Next up @ 0x%x:\n") % _pc).str();
                    const auto value = getUInt32BigEndian(_registerSet.readRegister(getImmediate(0)).bytes);

                    std::cerr << (boost::format("STW $%i $%i\nBase Address: %u\nEffective address: %u\nValue: %u\n") %
                        static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) %
                        _registerSet.readRegister(getImmediate(1)).getUInt32() % _registerSet                                                                                 .readRegister(getImmediate(1)).getUInt32() %                        value
                    ).str();

                    std::cout << "\n";
                }

                break;
            }

            case OpCode::SETB: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt8(getImmediate(1));
                break;
            }
            case OpCode::SETHW: {
                auto& reg = _registerSet.writeRegister(getImmediate(0));
                reg.zero();

                memcpy(&reg.bytes[register_set::Register::LSHW], &getImmediate(1), 2);
                break;
            }
            case OpCode::SETW: {
                memcpy(_registerSet.writeRegister(getImmediate(0)).bytes, &getImmediate(1), 4);
                break;
            }
            case OpCode::CP: {
                memcpy(_registerSet.writeRegister(getImmediate(0)).bytes, _registerSet.readRegister(getImmediate(1)).bytes,
                       4);
                break;
            }

            case OpCode::ADDF: throw InstructionNotImplementedInterrupt("ADDF", OpCode::ADDF);
            case OpCode::SUBF: throw InstructionNotImplementedInterrupt("SUBF", OpCode::SUBF);
            case OpCode::MULF: throw InstructionNotImplementedInterrupt("MULF", OpCode::MULF);
            case OpCode::DIVF: throw InstructionNotImplementedInterrupt("DIVF", OpCode::DIVF);

            case OpCode::LTF: throw InstructionNotImplementedInterrupt("LTF", OpCode::LTF);
            case OpCode::LEF: throw InstructionNotImplementedInterrupt("LEF", OpCode::LEF);
            case OpCode::GTF: throw InstructionNotImplementedInterrupt("GTF", OpCode::GTF);
            case OpCode::GEF: throw InstructionNotImplementedInterrupt("GEF", OpCode::GEF);
            case OpCode::ADDC: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        +
                                                                        getUInt32BigEndian(&getImmediate(2))
                                                                       );
                break;
            }
            case OpCode::SUBC: {
                _registerSet.writeRegister(getImmediate(0)).storeUInt32(
                                                                        _registerSet.readRegister(getImmediate(1)).getUInt32()
                                                                        -
                                                                        getUInt32BigEndian(&getImmediate(2))
                                                                       );
                break;
            }
            default: {
                throw UnknownOpCodeInterupt(op);
            }
        }
    } catch (HardwareInterrupt& e) {
        e.address = getProgramCounter();
        throw;
    }
}

void puck::Machine::jump(const uint32_t address) {
    _jumped = true;
    _pc = address;
}
