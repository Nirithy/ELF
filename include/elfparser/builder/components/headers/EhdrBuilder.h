#pragma once

#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryWriter.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Builder::Components {

    class EhdrBuilder {
    public:
        EhdrBuilder();

        // Setters for common fields
        void SetClass(Model::ElfClass cls);
        void SetData(Model::ElfData data);
        void SetOsAbi(Model::ElfOsAbi osabi);
        void SetType(Model::ElfType type);
        void SetMachine(Model::ElfMachine machine);
        void SetEntry(uint64_t entry);
        void SetFlags(uint32_t flags);

        // Update header with layout information
        void UpdateLayout(uint64_t phoff, uint16_t phnum, uint64_t shoff, uint16_t shnum, uint16_t shstrndx);

        const Model::Elf64_Ehdr& GetHeader() const;

        Common::Result Write(IO::BinaryWriter& writer);

    private:
        Model::Elf64_Ehdr m_header;
    };

}
