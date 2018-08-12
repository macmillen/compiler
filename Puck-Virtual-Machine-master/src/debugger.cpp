#include "debugger.h"
#include <iostream>
#include "endianess.h"
#include <cctype>

void puck::DebugLayer::printInstructionAtAddress(address_t address) {
    const auto oldPc = _pc;
    _pc = address;

    const auto op = getOpCode();

    switch (op) {
    case OpCode::ADD: {
        std::cerr << (boost::format(
                "ADD $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)
            ) % static_cast<int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::SUB: {
        std::cerr << (boost::format(
                "SUB $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)
            ) % static_cast<int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::MULU: {
        std::cerr << (boost::format("MULU $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::DIVU: {
        std::cerr << (boost::format("DIVU $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    }
    case OpCode::MODU: {
        std::cerr << (boost::format("MODU $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    }
    case OpCode::MULI: {
        std::cerr << (boost::format("MULI $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    }
    case OpCode::DIVI: {
        std::cerr << (boost::format("DIVI $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    }
    case OpCode::MODI: {
        std::cerr << (boost::format("MODI $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    }
    case OpCode::EQ: {
        std::cerr << (boost::format("EQ $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::NE: {
        std::cerr << (boost::format("NE $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::LTI: {
        std::cerr << (boost::format("LTI $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::LEI: {
        std::cerr << (boost::format("LEI $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::GTI: {
        std::cerr << (boost::format("GTI $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::GEI: {
        std::cerr << (boost::format("GEI $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::LTU: {
        std::cerr << (boost::format("LTU $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::LEU: {
        std::cerr << (boost::format("LEU $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::GTU: {
        std::cerr << (boost::format("GTU $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::GEU: {
        std::cerr << (boost::format("GEU $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) % static_cast<
                int>(getImmediate(2))
        ).str();
        break;
    }
    case OpCode::HALT:
        std::cerr << "HALT";
        break;
    case OpCode::BRT: {
        std::cerr << (boost::format("BRT $%i 0x%08X") % static_cast<int>(getImmediate(0)) % getUInt32BigEndian(
            &getImmediate(1))).str();
        break;
    }
    case OpCode::BRF: {
        std::cerr << (boost::format("BRF $%i 0x%08X") % static_cast<int>(getImmediate(0)) % getUInt32BigEndian(
            &getImmediate(1))).str();
        break;
    }
    case OpCode::JMP: {
        std::cerr << (boost::format("JMP 0x%08X") % getUInt32BigEndian(&getImmediate(1))).str();
        break;
    }
    case OpCode::JMPR: {
        std::cerr << (boost::format("JMPR $%i") % static_cast<int>(getImmediate(0))).str();
        break;
    }
    case OpCode::CALL: {
        std::cerr << (boost::format("CALL $%i 0x%08X") % static_cast<int>(getImmediate(0)) % getUInt32BigEndian(
            &getImmediate(1))).str();
        break;
    }
    case OpCode::INC: {
        std::cerr << (boost::format("INC $%i") % static_cast<int>(getImmediate(0))).str();
        break;
    }

    case OpCode::OUTC: {
        std::cerr << (boost::format("OUTC $%i") % static_cast<int>(getImmediate(0))).str();
        break;
    }
    case OpCode::INU: {
        std::cerr << (boost::format("INU $%i") % static_cast<int>(getImmediate(0))).str();
        break;
    }
    case OpCode::OUTU: {
        std::cerr << (boost::format("OUTU $%i") % static_cast<int>(getImmediate(0))).str();
        break;
    }
    case OpCode::INI: {
        std::cerr << (boost::format("INI $%i") % static_cast<int>(getImmediate(0))).str();
        break;
    }
    case OpCode::OUTI: {
        std::cerr << (boost::format("OUTI $%i") % static_cast<int>(getImmediate(0))).str();
        break;
    }
    case OpCode::INF: {
        std::cerr << (boost::format("INF $%i") % static_cast<int>(getImmediate(0))).str();
        break;
    }
    case OpCode::LDB: {
        byte value;
        _memory.readByteInto(&value,
                             _registerSet.readRegister(getImmediate(1)).getUInt32());

        std::cerr << (boost::format("LDB $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1))).str();
        break;
    }

    case OpCode::LDHW: {
        uint16_t value;
        _memory.readHalfwordInto(reinterpret_cast<byte*>(&value),
                                 _registerSet.readRegister(getImmediate(1)).getUInt32());

        std::cerr << (boost::format("LDHW $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1))).str();
        break;
    }
    case OpCode::LDW: {
        uint32_t value;
        _memory.readWordInto(reinterpret_cast<byte*>(&value),
                             _registerSet.readRegister(getImmediate(1)).getUInt32());

        std::cerr << (boost::format("LDW $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1))).str();
        break;
    }
    case OpCode::STB: {
        std::cerr << (boost::format("STB $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1))).str();
        break;
    }
    case OpCode::STHW: {
        std::cerr << (boost::format("STHW $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1))).str();
        break;
    }
    case OpCode::STW: {
        std::cerr << (boost::format("STW $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1))).str();
        break;
    }
    case OpCode::SETB: {
        std::cerr << (boost::format("SETB $%i 0x%x") % static_cast<int>(getImmediate(0)) % static_cast<unsigned int>(
            getImmediate(1))).str();
        break;
    }
    case OpCode::SETHW: {
        std::cerr << (boost::format("SETHW $%i 0x%x") % static_cast<int>(getImmediate(0)) % static_cast<unsigned int>(
            getUInt16BigEndian(&getImmediate(1)))).str();

        break;
    }
    case OpCode::SETW: {
        std::cerr << (boost::format("SETW $%i 0x%x") % static_cast<int>(getImmediate(0)) % static_cast<unsigned int>(
            getUInt32BigEndian(&getImmediate(1)))).str();

        break;
    }
    case OpCode::CP: {
        std::cerr << (boost::format("CP $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)
        )).str();
        break;
    }
    case OpCode::ADDC: {
        std::cerr << (boost::format("ADDC $%i $%i 0x%x") % static_cast<
            int>(getImmediate(0)) % static_cast<int>(getImmediate(1)
        ) % getUInt32BigEndian(&getImmediate(2))).str();
        break;
    }
    case OpCode::SUBC: {
        std::cerr << (boost::format("SUBC $%i $%i 0x%x") % static_cast<
            int>(getImmediate(0)) % static_cast<int>(getImmediate(1)
        ) % getUInt32BigEndian(&getImmediate(2))).str();
        break;
    }
    case OpCode::AND:
        std::cerr << (boost::format("AND $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::OR:
        std::cerr << (boost::format("OR $%i $%i $%i") %
            static_cast<int>(getImmediate(0)) % static_cast<int>(getImmediate(1)) %
            static_cast<
                int>(getImmediate(2))).str();
        break;
    case OpCode::XOR:
        std::cerr << (boost::format("XOR $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::SL:
        std::cerr << (boost::format("SL $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::SR:
        std::cerr << (boost::format("SR $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::CALLR: {
        std::cerr << (boost::format("CALLR $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1))).str();
        break;
    }

    case OpCode::OUTF: {
        std::cerr << (boost::format("OUTF $%i") % static_cast<int>(getImmediate(0))).str();
        break;
    }
    case OpCode::ADDF:
        std::cerr << (boost::format("ADDF $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::SUBF:
        std::cerr << (boost::format("SUBF $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::MULF:
        std::cerr << (boost::format("MULF $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::DIVF:
        std::cerr << (boost::format("DIVF $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::LTF:
        std::cerr << (boost::format("LTF $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::LEF:
        std::cerr << (boost::format("LEF $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::GTF:
        std::cerr << (boost::format("GTF $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    case OpCode::GEF:
        std::cerr << (boost::format("GEF $%i $%i $%i") % static_cast<int>(getImmediate(0)) % static_cast<int>(
            getImmediate(1)) % static_cast<int>(getImmediate(2))).str();
        break;
    default: std::cerr << (boost::format("Unknown instruction 0x%x") % static_cast<int>(op)).str();
    }

    _pc = oldPc;
}

void puck::DebugLayer::detailInstructionAtAddress(address_t address) {
    std::cerr << (boost::format("0x%08X: ") % address).str();
    printInstructionAtAddress(address);
    std::cerr << "\n";

    const auto oldPc = _pc;
    _pc = address;

    const auto op = getOpCode();
    switch (op) {
    case OpCode::ADD: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned + rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned + rightSigned;

        auto format = boost::format("Signed: %i + %i = %i\nUnsigned: %u + %u = %u\nHex: 0x%x + 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::SUB: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned - rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned - rightSigned;

        auto format = boost::format("Signed: %i - %i = %i\nUnsigned: %u - %u = %u\nHex: 0x%x - 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::MULU: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned * rightUnsigned;

        auto format = boost::format("Unsigned: %u * %u = %u\nHex: 0x%x * 0x%x = 0x%x");
        std::cerr << (format % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::DIVU: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned / rightUnsigned;

        auto format = boost::format("Unsigned: %u / %u = %u\nHex: 0x%x / 0x%x = 0x%x");
        std::cerr << (format % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::MODU: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned % rightUnsigned;

        auto format = boost::format("Unsigned: %u %% %u = %u\nHex: 0x%x %% 0x%x = 0x%x");
        std::cerr << (format % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::MULI: {
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned * rightSigned;

        auto format = boost::format("Signed: %i * %i = %i\nHex: 0x%x * 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftSigned % rightSigned % resultSigned).str();
        break;
    }
    case OpCode::DIVI: {
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned / rightSigned;

        auto format = boost::format("Signed: %i / %i = %i\nHex: 0x%x / 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftSigned % rightSigned % resultSigned).str();
        break;
    }
    case OpCode::MODI: {
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned % rightSigned;

        auto format = boost::format("Signed: %i %% %i = %i\nHex: 0x%x %% 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftSigned % rightSigned % resultSigned).str();
        break;
    }
    case OpCode::EQ: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned == rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned == rightSigned;

        auto format = boost::format("Signed: %i == %i = %i\nUnsigned: %u == %u = %u\nHex: 0x%x == 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::NE: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned != rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned != rightSigned;

        auto format = boost::format("Signed: %i != %i = %i\nUnsigned: %u != %u = %u\nHex: 0x%x != 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::LTI: {
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned < rightSigned;

        auto format = boost::format("Signed: %i < %i = %i\n\nHex: 0x%x < 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftSigned % rightSigned % resultSigned).str();
        break;
    }
    case OpCode::LEI: {
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned <= rightSigned;

        auto format = boost::format("Signed: %i <= %i = %i\nUnsigned: %u <= %u = %u\nHex: 0x%x <= 0x%x = 0x%x");

        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftSigned % rightSigned % resultSigned).str();
        break;
    }
    case OpCode::GTI: {
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned > rightSigned;

        auto format = boost::format("Signed: %i > %i = %i\nUnsigned: %u > %u = %u\nHex: 0x%x > 0x%x = 0x%x");

        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftSigned % rightSigned % resultSigned).str();
        break;
    }
    case OpCode::GEI: {
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned >= rightSigned;

        auto format = boost::format("Signed: %i >= %i = %i\nUnsigned: %u >= %u = %u\nHex: 0x%x >= 0x%x = 0x%x");

        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftSigned % rightSigned % resultSigned).str();
        break;
    }
    case OpCode::LTU: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned < rightUnsigned;

        auto format = boost::format("\nUnsigned: %u < %u = %u\nHex: 0x%x < 0x%x = 0x%x");
        std::cerr << (format % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::LEU: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned <= rightUnsigned;

        auto format = boost::format("\nUnsigned: %u <= %u = %u\nHex: 0x%x <= 0x%x = 0x%x");
        std::cerr << (format % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::GTU: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned > rightUnsigned;

        auto format = boost::format("\nUnsigned: %u > %u = %u\nHex: 0x%x > 0x%x = 0x%x");
        std::cerr << (format % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::GEU: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned >= rightUnsigned;

        auto format = boost::format("\nUnsigned: %u >= %u = %u\nHex: 0x%x >= 0x%x = 0x%x");
        std::cerr << (format % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::BRT: {
        std::cerr <<
        (_registerSet.readRegister(getImmediate(0)).getUInt8() != 0
             ? "Jump will be taken"
             : "Jump will not be taken") << "\n";
        break;
    }
    case OpCode::BRF: {
        std::cerr <<
        (_registerSet.readRegister(getImmediate(0)).getUInt8() == 0
             ? "Jump will be taken"
             : "Jump will not be taken") << "\n";
        break;
    }
    case OpCode::JMPR: {
        std::cerr << (boost::format("Will jump to 0x%08X\n") % _registerSet.readRegister(getImmediate(0)).getUInt32()).
            str();
        break;
    }
    case OpCode::CALL: {
        std::cerr << (boost::format("The return address will be: 0x%08X\n") % (_pc + getInstructionSize(op))).str();
        break;
    }
    case OpCode::OUTC: {
        const auto character = static_cast<char>(_registerSet.readRegister(getImmediate(0)).getUInt8());
        std::cerr << ((std::isprint(character) ? boost::format("Value: %c\n") : boost::format("Value: 0x%x\n")) %
            character).str();
        break;
    }
    case OpCode::OUTU: {
        std::cerr << (boost::format("Value: %u\n") % static_cast<char>(_registerSet
                                                                       .readRegister(getImmediate(0)).getUInt32())).
            str();
        break;
    }
    case OpCode::OUTI: {
        std::cerr << (boost::format("Value: %i\n") % static_cast<char>(_registerSet
                                                                       .readRegister(getImmediate(0)).getInt32())).
            str();
        break;
    }
    case OpCode::LDB: {
        byte value;
        _memory.readByteInto(&value,
                             _registerSet.readRegister(getImmediate(1)).getUInt32());

        std::cerr << (boost::format("Address: 0x%08X\nLoaded Value: 0x%x\n") %
            _registerSet.readRegister(getImmediate(1)).getUInt32() %
            value
        ).str();
        break;
    }

    case OpCode::LDHW: {
        uint16_t value;
        _memory.readHalfwordInto(reinterpret_cast<byte*>(&value),
                                 _registerSet.readRegister(getImmediate(1)).getUInt32());

        std::cerr << (boost::format("Address: 0x%08X\nLoaded Value: 0x%x\n") %
            _registerSet.readRegister(getImmediate(1)).getUInt32() %
            value
        ).str();
        break;
    }
    case OpCode::LDW: {
        uint32_t value;
        _memory.readWordInto(reinterpret_cast<byte*>(&value),
                             _registerSet.readRegister(getImmediate(1)).getUInt32());

        std::cerr << (boost::format("Address: 0x%08X\nLoaded Value: 0x%x\n") %
            _registerSet.readRegister(getImmediate(1)).getUInt32() %
            value
        ).str();
        break;
    }
    case OpCode::STB: {
        std::cerr << (boost::format("Address: 0x%08X\nStored Value: 0x%x\n") %
            _registerSet.readRegister(getImmediate(1)).getUInt32() %
            _registerSet.readRegister(getImmediate(0)).bytes[register_set::Register::LSB]
        ).str();
        break;
    }
    case OpCode::STHW: {
        const auto value = getUInt16BigEndian(
            &_registerSet.readRegister(getImmediate(0)).bytes[register_set::Register::LSHW]);

        std::cerr << (boost::format("Address: 0x%08X\nStored Value: 0x%x\n") %
            _registerSet.readRegister(getImmediate(1)).getUInt32() %
            value
        ).str();
        break;
    }
    case OpCode::STW: {
        const auto value = getUInt32BigEndian(_registerSet.readRegister(getImmediate(0)).bytes);

        std::cerr << (boost::format("Address: 0x%08X\nStored Value: 0x%x\n") %
            _registerSet.readRegister(getImmediate(1)).getUInt32() %
            value
        ).str();
        break;
    }
    case OpCode::ADDC: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = getUInt32BigEndian(&getImmediate(2));
        const auto resultUnsigned = leftUnsigned + rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = getInt32BigEndian(&getImmediate(2));
        const auto resultSigned = leftSigned + rightSigned;

        auto format = boost::format("Signed: %i + %i = %i\nUnsigned: %u + %u = %u\nHex: 0x%x + 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::SUBC: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = getUInt32BigEndian(&getImmediate(2));
        const auto resultUnsigned = leftUnsigned - rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = getInt32BigEndian(&getImmediate(2));
        const auto resultSigned = leftSigned - rightSigned;

        auto format = boost::format("Signed: %i + %i = %i\nUnsigned: %u + %u = %u\nHex: 0x%x + 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::AND: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned & rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned & rightSigned;

        auto format = boost::format("Signed: %i & %i = %i\nUnsigned: %u & %u = %u\nHex: 0x%x & 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::OR: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned | rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned | rightSigned;

        auto format = boost::format("Signed: %i | %i = %i\nUnsigned: %u | %u = %u\nHex: 0x%x | 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::XOR: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned ^ rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned ^ rightSigned;

        auto format = boost::format("Signed: %i ^ %i = %i\nUnsigned: %u ^ %u = %u\nHex: 0x%x ^ 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::SL: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned << rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned << rightSigned;

        auto format = boost::format("Signed: %i << %i = %i\nUnsigned: %u << %u = %u\nHex: 0x%x << 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::SR: {
        const auto leftUnsigned = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto rightUnsigned = _registerSet.readRegister(getImmediate(2)).getUInt32();
        const auto resultUnsigned = leftUnsigned >> rightUnsigned;
        const auto leftSigned = _registerSet.readRegister(getImmediate(1)).getInt32();
        const auto rightSigned = _registerSet.readRegister(getImmediate(2)).getInt32();
        const auto resultSigned = leftSigned >> rightSigned;

        auto format = boost::format("Signed: %i >> %i = %i\nUnsigned: %u >> %u = %u\nHex: 0x%x >> 0x%x = 0x%x");
        std::cerr << (format % leftSigned % rightSigned % resultSigned
            % leftUnsigned % rightUnsigned % resultUnsigned
            % leftUnsigned % rightUnsigned % resultUnsigned).str();
        break;
    }
    case OpCode::CALLR: {
        std::cerr << (boost::format("Will jump to 0x%08X\n The return address will be: 0x%08X\n") %
            _registerSet.readRegister(getImmediate(1)).getUInt32() %
            (_pc + getInstructionSize(op))
        ).str();
        break;
    }

    case OpCode::CP: {
        const auto unsign = _registerSet.readRegister(getImmediate(1)).getUInt32();
        const auto sign = _registerSet.readRegister(getImmediate(1)).getInt32();

        auto format = boost::format("Signed: %i\nUnsigned: %u\nHex: 0x%x");
        std::cerr << (format % sign % unsign % unsign).str();
        break;
    }

    case OpCode::JMP:
    case OpCode::HALT:
    case OpCode::INC:
    case OpCode::INU:
    case OpCode::INI:
    case OpCode::INF:
    case OpCode::OUTF:
    case OpCode::SETB:
    case OpCode::SETHW:
    case OpCode::SETW:
    case OpCode::ADDF:
    case OpCode::SUBF:
    case OpCode::MULF:
    case OpCode::DIVF:
    case OpCode::LTF:
    case OpCode::LEF:
    case OpCode::GTF:
    case OpCode::GEF:
        std::cerr << "No further details available";
        break;
    default: std::cerr << (boost::format("Unknown instruction 0x%08X\n") % static_cast<int>(op)).str();
    }

    _pc = oldPc;
}

void puck::DebugLayer::detailNextInstruction() {
    detailInstructionAtAddress(_pc);
}

void puck::DebugLayer::breakExecution() {
    _broken = true;
}

void puck::DebugLayer::continueExecution() {
    _broken = false;
}

void puck::DebugLayer::printHelp(boost::optional<std::string> command) {
    if (!command) {
        std::cerr << "Type \"? <command>\" for detailed info.\n";
        std::cerr << "The following commands are available:\n";
        std::cerr << " ?   : Show this help message\n";
        std::cerr << " b   : View and edit breakpoints\n";
        std::cerr << " c   : Continue execution\n";
        std::cerr << " i   : View instructions\n";
        std::cerr << " l   : List Instructions\n";
        std::cerr << " m   : Inspect memory\n";
        std::cerr << " r   : View registers\n";
        std::cerr << " q   : Quit execution\n";
        std::cerr << " s   : Single step execution\n";
    }
    else {
        const auto c = command.get();

        if (c == "b") {
            std::cerr << "\nDocumentation for \"b\":\n";
            std::cerr << "Used to edit breakpoints.\n";
            std::cerr <<
                "<address> can be either an unsigned decimal number or a hexadecimal number starting with \"0x\"\n\n";
            std::cerr << "Usage:\n";
            std::cerr << "  b              : Show active breakpoints\n";
            std::cerr << "  b add <address>: Add breakpoint\n";
            std::cerr << "  b rm <address> : Remove breakpoint\n";
            std::cerr << "  b clear        : Remove all breakpoints\n";
            std::cerr << "\n";
        }
        else if (c == "c") {
            std::cerr << "\nDocumentation for \"c\":\n";
            std::cerr << "Continues execution until breakpoint is hit.\n";
            std::cerr << "\n";
        }
        else if (c == "i") {
            std::cerr << "\nDocumentation for \"i\":\n";
            std::cerr << "Used to view instructions.\n";
            std::cerr <<
                "<address> can be either an unsigned decimal number or a hexadecimal number starting with \"0x\"\n\n";
            std::cerr << "Usage:\n";
            std::cerr << "  i              : View the next instruction\n";
            std::cerr << "  i <address>    : View instruction at the specified address\n";
            std::cerr << "\n";
        }
        else if (c == "s") {
            std::cerr << "\nDocumentation for \"s\":\n";
            std::cerr << "A single instruction is executed and execution will be paused again.\n";
            std::cerr << "\n";
        }
        else if (c == "r") {
            std::cerr << "\nDocumentation for \"r\"\n";
            std::cerr << "Shows the current contents of all 32 registers.\n";
            std::cerr << "\n";
        }
        else if (c == "q") {
            std::cerr << "\nDocumentation for \"q\":\n";
            std::cerr << "Quits the virtual machine.\n";
            std::cerr << "\n";
        }
        else if (c == "?") {
            std::cerr << "\nDocumentation for \"?\":\n";
            std::cerr << "Shows help for using this debugger..\n";
            std::cerr << "Usage:\n";
            std::cerr << "  ? <command>: Show details for a given command\n";
            std::cerr << "\n";
        }
        else if (c == "l") {
            std::cerr << "\nDocumentation for \"l\":\n";
            std::cerr << "Used to list instructions.\n";
            std::cerr <<
                "Note: Because the Virtual Machine does not distinguish code from static data, this only works correctly when there is only code up to this address.\nUse this only when you have no static data.\n\n";
            std::cerr <<
                "<address> can be either an unsigned decimal number or a hexadecimal number starting with \"0x\"\n";
            std::cerr << "<number of instructions> is an unsigned decimal number\n\n";
            std::cerr << "Usage:\n";
            std::cerr <<
                "  l <address> <number of instruction>: Lists the appropriate number of instructions starting at the address\n";
            std::cerr << "\n";
        }
        else if (c == "m") {
            std::cerr << "\nDocumentation for \"m\":\n";
            std::cerr << "Used to inspect memory in 16 byte chunks.\n";
            std::cerr <<
                "Note: Because the Virtual Machine does not distinguish code from static data, this only works correctly when there is only code up to this address.\n\n";
            std::cerr <<
                "<address> can be either an unsigned decimal number or a hexadecimal number starting with \"0x\"\n";
            std::cerr << "<number of chunks> is an unsigned decimal number\n\n";
            std::cerr << "Usage:\n";
            std::cerr << "  m <address> <number of chunks>: Shows the specified memory area as a hextable\n";
            std::cerr << "\n";
        }
        else {
            std::cerr << "Unknown command \"" << c << "\"\n";
        }
    }
}

puck::address_t puck::DebugLayer::parseAddress(std::string address) {
    address_t a;
    try {
        if (boost::starts_with(address, "0x")) {
            a = std::stoul(address.substr(2), nullptr, 16);
        }
        else {
            a = std::stoul(address);
        }
    }
    catch (std::invalid_argument&) {
        std::cerr << address << " is not a valid address\n";
        throw;
    } catch (std::out_of_range&) {
        std::cerr << address << " is out of range\n";
        throw;
    }

    return a;
}

void puck::DebugLayer::handleDebug() {
    std::cerr << (boost::format("Paused at 0x%08x:\n") % getProgramCounter()).str();
    std::cerr << "\n";

    while (_broken) {
        std::string line;
        std::getline(std::cin, line);
        std::vector<std::string> tokens;
        split(tokens, line, boost::is_any_of("\t "));

        if (!tokens.empty()) {
            if (tokens[0] == "c") {
                continueExecution();
            }
            else if (tokens[0] == "b") {
                switch (tokens.size()) {
                case 3: try {
                        if (tokens[1] == "add") _breakpoints.insert(parseAddress(tokens[2]));
                        else if (tokens[1] == "rm") _breakpoints.erase(parseAddress(tokens[2]));
                    }
                    catch (std::exception&) {
                    }
                    break;
                case 2:
                    if (tokens[1] == "clear") _breakpoints.clear();
                    else std::cerr << "Invalid arguments for breakpoint command\n";

                    break;
                case 1:
                    if (_breakpoints.empty()) {
                        std::cerr << "There are no current breakpoints\n";
                    }
                    else {
                        std::cerr << "All breakpoints:\n";
                        for (auto& b : _breakpoints) {
                            std::cerr << "  " << (boost::format("0x%08X") % b).str() << "\n";
                        }
                    }
                    break;
                default:
                    std::cerr << "Invalid arguments for breakpoint command\n";
                }
            }
            else if (tokens[0] == "?") {
                if (tokens.size() >= 2) printHelp(boost::optional<std::string>(tokens[1]));
                else printHelp(boost::none);
            }
            else if (tokens[0] == "s") {
                return;
            }
            else if (tokens[0] == "r") {
                std::cerr << " register |  unsigned  |   signed   |   hex    \n";
                std::cerr << "-----------------------------------------------\n";
                for (uint8_t i = 0; i < 32; ++i) {
                    std::cerr << (boost::format("    $%02u   | %10u | %10i | %08X\n")
                        % static_cast<uint32_t>(i)
                        % _registerSet.readRegister(i).getUInt32()
                        % _registerSet.readRegister(i).getInt32()
                        % _registerSet.readRegister(i).getUInt32()).str();
                }
            }
            else if (tokens[0] == "i") {
                switch (tokens.size()) {
                case 1:
                    detailNextInstruction();
                    std::cerr << "\n";
                    break;
                case 2: {
                    try {
                        detailInstructionAtAddress(parseAddress(tokens[1]));
                    }
                    catch (InvalidRegisterAccessInterrupt&) {
                        std::cerr << "Instruction appears to be using invalid registers.\n";
                    }
                    break;
                }
                default:
                    std::cerr << "Invalid arguments for instruction command\n";
                }
            }
            else if (tokens[0] == "q") {
                if (tokens.size() > 1) {
                    std::cerr << "Invalid arguments for quit command\n";
                }
                else {
                    exit(0);
                }
            }
            else if (tokens[0] == "m") {
                switch (tokens.size()) {
                case 3: {
                    const auto address = parseAddress(tokens[1]);
                    const auto lines = std::stoul(tokens[2]);
                    const auto min = address - address % 16;

                    std::cerr << "  Offset  ";

                    for (auto i = 0; i < 16; ++i) {
                        std::cerr << (boost::format(" %02X ") % i).str();
                    }
                    std::cerr << "\n";

                    for (address_t i = 0; i < lines; ++i) {
                        const auto base = min + i * 16;
                        std::cerr << (boost::format(" %08X ") % base).str();

                        for (address_t j = 0; j < 16; ++j) {
                            std::cerr << (boost::format(" %02X ") % static_cast<unsigned int>(_memory.getByte(base + j))
                            ).str();
                        }

                        std::cerr << "\n";
                    }
                    std::cerr << "\n";

                    break;
                }
                default:
                    std::cerr << "Invalid arguments for memory command\n";
                }
            }
            else if (tokens[0] == "l") {
                switch (tokens.size()) {
                case 3: {
                    const auto address = parseAddress(tokens[1]);
                    const auto instructions = std::stoul(tokens[2]);

                    address_t instructionAddress = 0;
                    while (instructionAddress + getInstructionSize(
                        static_cast<OpCode>(_memory.getByte(instructionAddress))) <= address) {
                        instructionAddress += getInstructionSize(
                            static_cast<OpCode>(_memory.getByte(instructionAddress)));
                    }

                    for (size_t i = 0; i < instructions; ++i) {
                        std::cerr << (boost::format("0x%08X: ") % instructionAddress).str();
                        printInstructionAtAddress(instructionAddress);
                        std::cerr << "\n";
                        instructionAddress += getInstructionSize(
                            static_cast<OpCode>(_memory.getByte(instructionAddress)));
                    }
                }
                break;
                default:
                    std::cerr << "Invalid arguments for list command\n";
                }
            }
            else {
                printHelp(boost::none);
            }
        }

    }
}

puck::DebugLayer::DebugLayer(bool failWhenWritingCode)
    :
    Machine(failWhenWritingCode) {
}

void puck::DebugLayer::executeInstruction() {
    if (std::find(_breakpoints.begin(), _breakpoints.end(), getProgramCounter()) != _breakpoints.end()) {
        std::cerr << "Hit breakpoint\n";
        breakExecution();

    }

    if (_broken) handleDebug();

    try {
        this->Machine::executeInstruction();

    }
    catch (HardwareInterrupt& e) {
        std::cerr << "\n" << e.what() << "\n";
        if (e.address) {
            std::cerr << (boost::format("Offending Instruction @ 0x%X:\n") % e.address.get()).str();
            printInstructionAtAddress(e.address.get());
            std::cerr << "\n";

        }
        std::cerr << "Execution paused by interrupt\n";
        breakExecution();

    }
}
