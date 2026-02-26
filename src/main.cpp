#include <iostream>
#include <iomanip>
#include "elfparser/parser/ElfParser.h"
#include "elfparser/utils/Logger.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <elf_file>" << std::endl;
        return 1;
    }

    std::string filepath = argv[1];

    // Configure logger
    ElfParser::Utils::Logger::Get().SetLevel(ElfParser::Utils::LogLevel::Info);

    ElfParser::Parser::ElfParser parser(filepath);
    auto result = parser.Parse();

    if (!result.IsOk()) {
        ElfParser::Utils::Logger::Error("Parsing failed: " + result.message);
        return 1;
    }

    const auto& header = parser.GetHeader();
    std::cout << "Successfully parsed " << filepath << std::endl;
    std::cout << "Entry Point: 0x" << std::hex << header.e_entry << std::dec << std::endl;
    std::cout << "Program Headers: " << header.e_phnum << std::endl;
    std::cout << "Section Headers: " << header.e_shnum << std::endl;

    std::cout << "\nSections:" << std::endl;
    std::cout << std::left << std::setw(30) << "Name"
              << std::setw(10) << "Type"
              << std::setw(16) << "Addr"
              << std::setw(16) << "Offset"
              << std::setw(16) << "Size" << std::endl;

    const auto& sections = parser.GetSectionHeaders();
    for (const auto& sh : sections) {
        std::string name = parser.GetSectionName(sh.sh_name);
        if (name.empty()) name = "<noname>";

        std::cout << std::left << std::setw(30) << name
                  << std::hex
                  << std::setw(10) << sh.sh_type
                  << std::setw(16) << sh.sh_addr
                  << std::setw(16) << sh.sh_offset
                  << std::setw(16) << sh.sh_size
                  << std::dec << std::endl;
    }

    return 0;
}
