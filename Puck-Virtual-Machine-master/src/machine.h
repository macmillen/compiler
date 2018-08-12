#pragma once
#include "executable.h"
#include <boost/format.hpp>
#include "hardwareinterrupt.h"

namespace puck {
    using address_t = uint32_t;

    class CodeOverwrittenInterrupt : public HardwareInterrupt {
    public:
        explicit CodeOverwrittenInterrupt(const address_t address)
            : HardwareInterrupt((boost::format("Code overwritten at 0x%08X") % address).str()) { }
    };

    class Machine {
    protected:
        bool _isHalted;

        using byte = uint8_t;

        static constexpr uint8_t REGISTER_COUNT = 32;
        static constexpr uint32_t MEMORY_SIZE = 32 * 1024 * 1024;

        class register_set {
        public:
            struct Register {
                static constexpr int MSB = 0;
                static constexpr int LSB = 3;
                static constexpr int LSHW = 2;
                static constexpr int MSHW = 0;

                byte bytes[4] = {0, 0, 0, 0};

                uint32_t getUInt32() const;
                void storeUInt32(uint32_t value);

                int32_t getInt32() const;
                void storeInt32(int32_t value);

                int8_t getUInt8() const;
                void storeUInt8(int8_t value);

                void zero() {
                    memset(bytes, 0, 4);
                }
            };

        private:
            Register _registers[REGISTER_COUNT];

        public:
            const Register& readRegister(uint8_t n) const;

            Register& writeRegister(uint8_t n);
        } _registerSet;

        class memory {
            byte _memory[MEMORY_SIZE] = {}; //32 Megabyte memory

            void checkAddress(address_t address) const;

        public:
            size_t codeSize = 0;
            bool failWhenWritingCode = false;

            void readByteInto(byte* dst, address_t address) const;

            void readHalfwordInto(byte* dst, address_t address) const;

            void readWordInto(byte* dst, address_t address) const;

            void storeByte(byte const* src, address_t address);

            void storeHalfword(byte const* src, address_t address);

            bool storeWord(byte const* src, address_t address);

            byte& getByte(address_t address);

            byte* getBasePointer();

            static uint32_t getMemorySize() {
                return sizeof _memory;
            }
        } _memory;

        uint32_t _pc;
        bool _jumped = false;

    public:
        virtual ~Machine() = default;
        explicit Machine(bool failWhenWritingCode);

        void loadExecutable(std::ifstream& stream);

        bool isHalted() const {
            return _isHalted;
        }

        auto getProgramCounter() const {
            return _pc;
        }

        virtual void executeInstruction();

    protected:
        OpCode getOpCode();

        uint8_t& getImmediate(uint8_t n);

        void jump(uint32_t address);
    };

    class ProgramRunner {
        Machine& _machine;

    public:
        explicit ProgramRunner(Machine& machine)
            : _machine(machine) { }

        void run() const;
    };
}
