#include "executable.h"
#include "endianess.h"
#include <boost/format.hpp>
#include <fstream>

uint8_t puck::getInstructionSize(const OpCode opcode) {
    using puck::OpCode;
    switch (opcode) {
        case OpCode::ADD:
        case OpCode::SUB:
        case OpCode::MULU:
        case OpCode::DIVU:
        case OpCode::MODU:
        case OpCode::MULI:
        case OpCode::DIVI:
        case OpCode::MODI: return 4;

        case OpCode::AND:
        case OpCode::OR:
        case OpCode::XOR:
        case OpCode::SL:
        case OpCode::SR: return 4;

        case OpCode::EQ:
        case OpCode::NE:
        case OpCode::LTI:
        case OpCode::LEI:
        case OpCode::GTI:
        case OpCode::GEI:
        case OpCode::LTU:
        case OpCode::LEU:
        case OpCode::GTU:
        case OpCode::GEU: return 4;

        case OpCode::BRT: return 6;
        case OpCode::BRF: return 6;
        case OpCode::JMP: return 5;
        case OpCode::JMPR: return 2;
        case OpCode::CALL: return 6;
        case OpCode::CALLR: return 3;
        case OpCode::HALT: return 1;

        case OpCode::LDB:
        case OpCode::LDHW:
        case OpCode::LDW:
        case OpCode::STB:
        case OpCode::STHW:
        case OpCode::STW: return 3;

        case OpCode::INC:
        case OpCode::OUTC:
        case OpCode::INU:
        case OpCode::OUTU:
        case OpCode::INI:
        case OpCode::OUTI:
        case OpCode::INF:
        case OpCode::OUTF: return 2;

        case OpCode::SETB: return 3;
        case OpCode::SETHW: return 4;
        case OpCode::SETW: return 6;
        case OpCode::CP: return 3;

        case OpCode::ADDF:
        case OpCode::SUBF:
        case OpCode::MULF:
        case OpCode::DIVF: return 4;

        case OpCode::LTF:
        case OpCode::LEF:
        case OpCode::GTF:
        case OpCode::GEF: return 4;

        case OpCode::ADDC: ;
        case OpCode::SUBC: return 7;
        default: return 0;
    }
}

size_t puck::readExecutable(std::ifstream& stream, uint8_t* targetMemory) {
    static constexpr uint32_t MAGIC_NUMBER = 0x5055434B;
    const ExecutableHeader header{stream};

    if (header.magicNumber != MAGIC_NUMBER) throw std::runtime_error("The input file does not appear to contain valid bytecode");

    if (!stream.read(reinterpret_cast<char*>(targetMemory), header.byteCount)) {
        throw std::runtime_error("File ended unexpectedly");
    }

    if (stream.peek() != EOF) {
        throw std::runtime_error("File is larger than expected");
    }

    return header.byteCount;
}

puck::ExecutableHeader::ExecutableHeader()
    : magicNumber{0},
      byteCount{0} {}

puck::ExecutableHeader::ExecutableHeader(std::ifstream& stream) {
    if (!stream.read(reinterpret_cast<char*>(&magicNumber), 4)) throw std::runtime_error("File ended unexpectedly"); //Read four bytes into the magicNumber member
    magicNumber = getUInt32BigEndian(reinterpret_cast<uint8_t*>(&magicNumber)); //Convert from BigEndian into native

    if (!stream.read(reinterpret_cast<char*>(&byteCount), 4)) throw std::runtime_error("File ended unexpectedly when reading byte count"); //Read four bytes into the byteCount member
    byteCount = getUInt32BigEndian(reinterpret_cast<uint8_t*>(&byteCount)); //Convert from BigEndian into native
}
