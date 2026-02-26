#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <type_traits>
#include "elfparser/common/Types.h"
#include "elfparser/utils/Endian.h"

namespace ElfParser::IO {

    class BinaryReader {
    public:
        BinaryReader(const std::string& filepath);
        ~BinaryReader();

        // Delete copy/move to avoid issues with fstream
        BinaryReader(const BinaryReader&) = delete;
        BinaryReader& operator=(const BinaryReader&) = delete;

        bool Open();
        void Close();

        // Set the expected endianness of the file.
        // If it differs from the host system, Read<T> will swap bytes.
        void SetLittleEndian(bool isLittleEndian);

        // Check if swapping is enabled
        bool ShouldSwap() const { return m_shouldSwap; }

        // Read raw bytes into a buffer
        bool Read(void* buffer, std::streamsize size);

        // Template to read primitive types directly with automatic endian swapping
        template<typename T>
        bool Read(T& value) {
            if (!Read(&value, sizeof(T))) {
                return false;
            }
            if (m_shouldSwap) {
                if constexpr (std::is_arithmetic<T>::value) {
                    value = Utils::Swap(value);
                }
            }
            return true;
        }

        // Seek to an absolute position
        bool Seek(std::streampos pos);

        // Get current position
        std::streampos Tell();

        // Get total file size
        std::streamsize GetSize();

        // Read a null-terminated string with a safety limit
        bool ReadString(std::string& str, size_t maxLength = 256);

    private:
        std::string m_filepath;
        std::ifstream m_stream;
        std::streamsize m_fileSize;
        bool m_shouldSwap = false;
    };

}
