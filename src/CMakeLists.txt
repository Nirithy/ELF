# Set library sources
set(LIB_SOURCES
    utils/Logger.cpp
    io/BinaryReader.cpp
    io/BinaryWriter.cpp
    parser/ElfParser.cpp
    parser/components/headers/EhdrParser.cpp
    parser/components/headers/PhdrParser.cpp
    parser/components/headers/ShdrParser.cpp
    parser/components/sections/SymbolTableParser.cpp
    parser/components/sections/DynamicSectionParser.cpp
    parser/components/sections/RelocationSectionParser.cpp
    parser/components/sections/notes/NoteSectionParser.cpp
    parser/components/sections/hash/HashSectionParser.cpp
    parser/components/sections/hash/GnuHashSectionParser.cpp
    parser/components/sections/version/VersionDefinitionParser.cpp
    parser/components/sections/version/VersionRequirementParser.cpp
    parser/components/sections/strings/StringTableParser.cpp
    builder/ElfBuilder.cpp
    builder/components/headers/EhdrBuilder.cpp
    builder/components/headers/PhdrBuilder.cpp
    builder/components/headers/ShdrBuilder.cpp
    builder/components/sections/SectionBuilder.cpp
    builder/components/sections/strings/StringTableBuilder.cpp
    builder/components/sections/symbols/SymbolTableBuilder.cpp
    builder/components/sections/dynamic/DynamicSectionBuilder.cpp
    builder/components/sections/hash/HashSectionBuilder.cpp
    builder/components/sections/hash/GnuHashSectionBuilder.cpp
    builder/components/sections/notes/NoteSectionBuilder.cpp
    builder/components/sections/version/VersionDefinitionBuilder.cpp
    builder/components/sections/version/VersionRequirementBuilder.cpp
    builder/components/sections/relocations/RelocationSectionBuilder.cpp
    builder/layout/LayoutManager.cpp
    factory/SectionFactory.cpp
    factory/SegmentFactory.cpp
)

# Create the core library
add_library(libelfparser ${LIB_SOURCES})

# Public include directory for consumers
target_include_directories(libelfparser PUBLIC ${CMAKE_SOURCE_DIR}/include)

# CLI Executable
add_executable(elf_parser_cli main.cpp)

# Link CLI with the library
target_link_libraries(elf_parser_cli PRIVATE libelfparser)
