#pragma once

#include "elfparser/common/Types.h"
#include <string>
#include <vector>
#include <cstdint>

namespace ElfParser::Plugins::API {

    /**
     * @brief Interface for file system operations exposed to plugins.
     */
    class IFileSystemAPI {
    public:
        virtual ~IFileSystemAPI() = default;

        /**
         * @brief Read a file into a buffer.
         * @param path The path to the file.
         * @return A vector containing the file contents, or empty on failure.
         */
        virtual std::vector<uint8_t> ReadFile(const std::string& path) = 0;

        /**
         * @brief Write a buffer to a file.
         * @param path The path to the file.
         * @param data The data to write.
         * @return Result indicating success or failure.
         */
        virtual Common::Result WriteFile(const std::string& path, const std::vector<uint8_t>& data) = 0;

        /**
         * @brief Check if a file exists.
         * @param path The path to the file.
         * @return True if exists, false otherwise.
         */
        virtual bool Exists(const std::string& path) const = 0;
    };

}
