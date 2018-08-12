#pragma once
#include "machine.h"
#include <boost/algorithm/string.hpp>
#include <set>

namespace puck {
    class DebugLayer : public Machine {
        void printInstructionAtAddress(address_t address);

        void detailInstructionAtAddress(address_t address);

        void detailNextInstruction();

        bool _broken = true;

        void breakExecution();

        void continueExecution();

        std::set<uint32_t> _breakpoints;

        static void printHelp(boost::optional<std::string> command);

        static address_t parseAddress(std::string address);

        void handleDebug();

    public
    :
        explicit DebugLayer(
            bool failWhenWritingCode
        );

        void executeInstruction() override;
    };
}
