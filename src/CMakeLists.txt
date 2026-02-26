# Set library sources
set(LIB_SOURCES
    utils/Logger.cpp
    io/BinaryReader.cpp
    io/BinaryWriter.cpp
    parser/ElfParser.cpp
    parser/components/headers/EhdrParser.cpp
    parser/components/headers/PhdrParser.cpp
    parser/components/headers/ShdrParser.cpp
    parser/components/sections/symbols/SymbolTableParser.cpp
    parser/components/sections/dynamic/DynamicSectionParser.cpp
    parser/components/sections/relocations/RelocationSectionParser.cpp
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
    builder/components/segments/SegmentBuilder.cpp
    builder/components/segments/LoadSegmentBuilder.cpp
    builder/components/segments/DynamicSegmentBuilder.cpp
    builder/components/segments/NoteSegmentBuilder.cpp
    builder/layout/LayoutManager.cpp
    builder/layout/strategies/DefaultLayoutStrategy.cpp
    builder/layout/strategies/CompactLayoutStrategy.cpp
    builder/components/segments/calculators/DefaultSegmentCalculator.cpp
    builder/components/segments/calculators/LoadSegmentCalculator.cpp
    builder/components/segments/calculators/DynamicSegmentCalculator.cpp
    factory/SectionFactory.cpp
    factory/SegmentFactory.cpp
    factory/SymbolFactory.cpp
    factory/RelocationFactory.cpp
    factory/DynamicEntryFactory.cpp
    factory/NoteFactory.cpp
    factory/VersionFactory.cpp
    arch/ArchFactory.cpp
    arch/x86_64/X86_64Handler.cpp
    arch/aarch64/AArch64Handler.cpp
    arch/riscv/RiscvHandler.cpp
    validator/components/EhdrValidator.cpp
    validator/components/PhdrValidator.cpp
    validator/components/ShdrValidator.cpp
    transform/actions/StripSymbolsAction.cpp
    transform/actions/RemoveSectionAction.cpp
    plugins/core/PluginManager.cpp
    plugins/core/PluginContext.cpp
    plugins/events/EventDispatcher.cpp
    plugins/registry/PluginRegistry.cpp
    plugins/loaders/StaticPluginLoader.cpp
)

# Create the core library
add_library(libelfparser ${LIB_SOURCES})

# Public include directory for consumers
target_include_directories(libelfparser PUBLIC ${CMAKE_SOURCE_DIR}/include)

# CLI Executable
add_executable(elf_parser_cli main.cpp)

# Link CLI with the library
target_link_libraries(elf_parser_cli PRIVATE libelfparser)
