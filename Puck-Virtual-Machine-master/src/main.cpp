#include <boost/program_options.hpp>
#include <iostream>
#include "machine.h"
#include "debugger.h"
#include <fstream>

int main(const int argc, char** args) {
    using namespace boost::program_options;
    options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("input-file", value<std::string>(), "set input file")
        ("debug", "enable debugger")
        ("interupt-when-writing-code", "Interrupts when executing a store instruction at the code area");

    positional_options_description p;
    p.add("input-file", 1);

    variables_map vm;
    try {
        store(command_line_parser(argc, args).options(desc).positional(p).run(), vm);
        notify(vm);
    }
    catch (unknown_option& e) {
        std::cerr << "Unknown option: " << e.get_option_name() << "\n";
        return 1;
    }

    if (vm.count("help")) {
        std::cerr << desc << "\n";
        return 1;
    }

    if (!vm.count("input-file")) {
        std::cerr << "Input file not set.\n";
        return -1;
    }

    const auto input = vm["input-file"].as<std::string>();
    std::cerr << "Input file: " << input << "\n";

    auto stream = std::ifstream(input, std::ios::binary);
    if (!stream.good()) {
        std::cerr << "Input file " << input << " does not exist!\n";
        return -1;
    }

    try {
        const auto failWhenWritingCode = vm.count("interupt-when-writing-code");

        const auto m = vm.count("debug")
                           ? std::make_unique<puck::DebugLayer>(failWhenWritingCode)
                           : std::make_unique<puck::Machine>(failWhenWritingCode);

        m->loadExecutable(stream);
        puck::ProgramRunner(*m).run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return -1;
    }
}
