#pragma once

#include <exception>

namespace puck {
    class HardwareInterrupt : public std::exception {
        std::string _msg;

    protected:
        explicit HardwareInterrupt(std::string message)
                : _msg(std::move(message)) {}

    public:
        const char *what() const noexcept override {
            return _msg.data();
        }

        boost::optional<uint32_t> address = boost::none;
    };

    class InvalidRegisterAccessInterrupt : public HardwareInterrupt {
    public:
        explicit InvalidRegisterAccessInterrupt(char const *message)
                : HardwareInterrupt(message) {}
    };

    class UnknownOpCodeInterupt : public HardwareInterrupt {
    public:
        explicit UnknownOpCodeInterupt(OpCode opCode)
                : HardwareInterrupt(
                    (boost::format("Unknown instruction 0x%2X") % static_cast<uint8_t>(opCode)).str()) {}
    };

    class SegfaultInterrupt : public HardwareInterrupt {
    public:
        explicit SegfaultInterrupt(char const *message)
                : HardwareInterrupt(message) {}
    };

    class InstructionNotImplementedInterrupt : public HardwareInterrupt {
    public:
        InstructionNotImplementedInterrupt(const std::string instruction, OpCode opCode)
            : HardwareInterrupt((boost::format("%s Instruction with op code %2X is not implemented") % instruction % static_cast<uint8_t>(opCode)).str()) { }
    };

    class DividedByZeroInterrupt : public HardwareInterrupt {
    public:
        explicit DividedByZeroInterrupt(const uint32_t address)
            : HardwareInterrupt((boost::format("Division by zero when executing address 0x%8x") % address).str()) { }

    };

    class InvalidJumpInterrupt : public HardwareInterrupt {
    public:
        explicit InvalidJumpInterrupt(const uint32_t address)
            : HardwareInterrupt((boost::format("Invalid jump to 0x%8X") % address).str()) { }
    };
}
