#pragma once

#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include <string>
#include <vector>
#include <memory>

namespace ElfParser::Plugins::API {

    /**
     * @brief Interface for accessing core ELF functionality from plugins.
     * This facade ensures plugins don't depend directly on internal implementation details.
     */
    class IElfAPI {
    public:
        virtual ~IElfAPI() = default;

        /**
         * @brief Get the current ELF header.
         * @return The ELF header structure.
         */
        virtual const Model::Elf64_Ehdr& GetHeader() const = 0;

        /**
         * @brief Get a section header by name.
         * @param name The name of the section.
         * @return Pointer to the section header, or nullptr if not found.
         */
        virtual const Model::Elf64_Shdr* GetSectionHeader(const std::string& name) const = 0;

        /**
         * @brief Get all section headers.
         * @return A list of all section headers.
         */
        virtual std::vector<Model::Elf64_Shdr> GetSectionHeaders() const = 0;

        /**
         * @brief Check if the ELF file is 64-bit.
         * @return True if 64-bit, false otherwise.
         */
        virtual bool Is64Bit() const = 0;

        /**
         * @brief Check if the ELF file is big-endian.
         * @return True if big-endian, false otherwise.
         */
        virtual bool IsBigEndian() const = 0;
    };

}
