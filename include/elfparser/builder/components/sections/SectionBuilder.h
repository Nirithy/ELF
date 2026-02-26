#pragma once

#include <string>
#include <cstdint>
#include "elfparser/io/BinaryWriter.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Builder::Components {

    class SectionBuilder {
    public:
        virtual ~SectionBuilder() = default;

        // Setters for section header fields
        void SetName(const std::string& name);
        void SetType(Model::ElfSectionType type);
        void SetFlags(uint64_t flags);
        void SetAddr(uint64_t addr);
        void SetAddralign(uint64_t align);
        void SetLink(uint32_t link);
        void SetInfo(uint32_t info);
        void SetEntSize(uint64_t entsize);

        // Getters
        const std::string& GetName() const;
        Model::Elf64_Shdr& GetHeader();
        const Model::Elf64_Shdr& GetHeader() const;

        // Abstract method to write the section content
        virtual Common::Result Write(IO::BinaryWriter& writer) = 0;

        // Abstract method to get the size of the section content
        virtual uint64_t GetSize() const = 0;

        // Update the header with offset and size (called by ElfBuilder)
        void UpdateHeader(uint64_t offset, uint64_t size);

    protected:
        std::string m_name;
        Model::Elf64_Shdr m_header{};
    };

}
