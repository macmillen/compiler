#pragma once

#include <boost/filesystem.hpp>
#include <boost/format/format_fwd.hpp>

namespace puck {
    enum class OpCode : uint8_t {
        //(un-)signed integer arithmetic
        ADD = 0x00,
        //  add   dstR, op1R, op2R                  dst := op1R + op2R
        SUB = 0x01,
        //  sub   dstR, op1R, op2R                  dst := op1R - op2R
        MULU = 0x02,
        // mulu  dstR, op1R, op2R                  dst := op1R * op2R (unsigned integer multiplication)
        DIVU = 0x03,
        // divu  dstR, op1R, op2R                  dst := op1R / op2R (unsigned integer division)
        MODU = 0x04,
        // modu  dstR, op1R, op2R                  dst := op1R / op2R (unsigned integer modulo)
        MULI = 0x05,
        // mul   dstR, op1R, op2R                  dst := op1R * op2R (signed integer multiplication)
        DIVI = 0x06,
        // div   dstR, op1R, op2R                  dst := op1R / op2R (signed integer division)
        MODI = 0x07,
        // rem   dstR, op1R, op2R                  dst := op1R % op2R (signed integer modulo)

        //bitwise operators
        AND = 0x10,
        //  and   dstR, op1R, op2R                  dst := op1R & op2R (bitwise and)
        OR = 0x11,
        //   or    dstR, op1R, op2R                  dst := op1R | op2R (bitwise or)
        XOR = 0x12,
        //  xor   dstR, op1R, op2R                  dst := op1R ^ op2R (bitwise xor)
        SL = 0x13,
        //   sl    dstR, op1R, op2R                  dst := op1R << op2R (bitwise left shift (towards the MSB), op2 is interpreted as an unsigned 8bit integer)
        SR = 0x14,
        //   sr    dstR, op1R, op2R                  dst := op1R >> op2R (bitwise right shift (towards the LSB), op2 is interpreted as an unsigned 8bit integer);

        //(un-)signed integer comparisons
        EQ = 0x20,
        //   eq    dstR, op1R, op2R                  dst := op1R == op2R (compares all 4 bytes)
        NE = 0x21,
        //   ne    dstR, op1R, op2R                  dst := op1R != op2R (compares all 4 bytes)
        LTI = 0x22,
        //  lti   dstR, op1R, op2R                  dst := op1R < op2R (signed 32bit integer)
        LEI = 0x23,
        //  lei   dstR, op1R, op2R                  dst := op1R <= op2R (signed 32bit integer)
        GTI = 0x24,
        //  gti   dstR, op1R, op2R                  dst := op1R > op2R (signed 32bit integer)
        GEI = 0x25,
        //  gei   dstR, op1R, op2R                  dst := op1R >= op2R (signed 32bit integer)
        LTU = 0x26,
        //  ltu   dstR, op1R, op2R                  dst := op1R < op2R (unsigned 32bit integer)
        LEU = 0x27,
        //  leu   dstR, op1R, op2R                  dst := op1R <= op2R (unsigned 32bit integer)
        GTU = 0x28,
        //  gtu   dstR, op1R, op2R                  dst := op1R > op2R (unsigned 32bit integer)
        GEU = 0x29,
        //  geu   dstR, op1R, op2R                  dst := op1R >= op2R (unsigned 32bit integer)

        //Program flow control
        BRT = 0x30,
        //  brt   srcR, 4 byte immediate            if least significant byte of srcR != 0 => program counter := immediate value
        BRF = 0x31,
        //  brf   srcR, 4 byte immediate            if least significant byte of srcR == 0 => program counter := immediate value
        JMP = 0x32,
        //  jmp   4 byte immediate                  unconditionally jumps to the address in the immediate value.
        JMPR = 0x33,
        // jmpr  dstR                              unconditionally jumps to the address in dstR.                   This is used to return from call
        CALL = 0x34,
        // call  retR, 4 byte immediate            unconditionally jumps to the address in the immediate value.    retR := return-address
        CALLR = 0x35,
        //call  retR, dstR                        unconditionally jumps to the address in dstR.                   retR := return-address
        HALT = 0x36,
        // halt                                    Stops execution

        //memory operations
        LDB = 0x40,
        //  ldb   dstR, srcR, 1 byte uint offset    dstR := byte@memory[srcR + offset]              srcR is interpreted as 32 bit uint, all other bytes are set to 0
        LDHW = 0x41,
        // ldhw  dstR, srcR, 1 byte uint offset    dstR := halfword@memory[srcR + offset]          srcR is interpreted as 32 bit uint, all other bytes are set to 0
        LDW = 0x42,
        //  ldw   dstR, srcR, 1 byte uint offset    dstR := word@memory[srcR + offset]              srcR is interpreted as 32 bit uint
        STB = 0x43,
        //  stb   srcR, dstR, 1 byte uint offset    byte@memory[dstR + offset] := LSB@srcR
        STHW = 0x44,
        // sthw  srcR, dstR, 1 byte uint offset    halfword@memory[dstR + offset] := LSHW@srcR
        STW = 0x45,
        //  stw   srcR, dstR, 1 byte uint offset    word@memory[dstR + offset] := srcR

        //I/O operations
        INC = 0x50,
        //  inc   dstR                              reads a single byte from stdin and places it in the least significant byte of dstR, all other bytes will be set to 0
        OUTC = 0x51,
        // outc  srcR                              Prints the least significant byte of srcR as a character
        INU = 0x52,
        // inui  dstR                              Parses an unsigned 32 bit int from stdin and places it in dstR
        OUTU = 0x53,
        //outui srcR                              Prints the content of srcR as 32 bit unsigned integer tp stdout
        INI = 0x54,
        //  ini   dstR                              Parses a signed 32 bit int from stdin and places it in dstR
        OUTI = 0x55,
        // outi  srcR                              Prints the content of srcR as 32 bit signed integer to stdout
        INF = 0x56,
        //  inf   dstR                              Parses a 32 bit floating point and places it in dstR
        OUTF = 0x57,
        // outf  srcR                              Prints the content of srcR as 32 bit floating point to stdout

        //loading constant data into registers
        SETB = 0x60,
        // setb  dstR, 1 byte immediate            LSB@dstR := immediate, all other bytes are set to 0
        SETHW = 0x61,
        //sethw dstR, 2 byte immediate            LSHW@dstR := immediate, all other bytes are set to 0
        SETW = 0x62,
        // setw  dstR, 4 byte immediate            dstR := immediate
        CP = 0x63,

        //floating point operations
        ADDF = 0x70,
        SUBF = 0x71,
        MULF = 0x72,
        DIVF = 0x73,

        //floating point comparisons
        LTF = 0x80,
        LEF = 0x81,
        GTF = 0x82,
        GEF = 0x83,

        //operators with immediate operands
        ADDC = 0x90,
        //addc dstR, op1R, 4 byte immediate value
        SUBC = 0x91,
        //subc dstR, op1R, 4 byte immediate value
    };

    uint8_t getInstructionSize(OpCode opcode);

    struct ExecutableHeader {
        uint32_t magicNumber;
        uint32_t byteCount;

        ExecutableHeader();

        explicit ExecutableHeader(std::ifstream& stream);
    };

    size_t readExecutable(std::ifstream& stream, uint8_t* targetMemory);

}
