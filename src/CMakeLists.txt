# Set library sources
set(LIB_SOURCES
    utils/Logger.cpp
    io/BinaryReader.cpp
    parser/ElfParser.cpp
    parser/components/headers/EhdrParser.cpp
    parser/components/headers/PhdrParser.cpp
    parser/components/headers/ShdrParser.cpp
    parser/components/sections/SymbolTableParser.cpp
    parser/components/sections/DynamicSectionParser.cpp
    parser/components/sections/RelocationSectionParser.cpp
)

# Create the core library
add_library(libelfparser ${LIB_SOURCES})

# Public include directory for consumers
target_include_directories(libelfparser PUBLIC ${CMAKE_SOURCE_DIR}/include)

# CLI Executable
add_executable(elf_parser_cli main.cpp)

# Link CLI with the library
target_link_libraries(elf_parser_cli PRIVATE libelfparser)
