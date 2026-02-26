#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "elfparser/common/Types.h"

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

        // Read raw bytes into a buffer
        bool Read(void* buffer, std::streamsize size);

        // Template to read primitive types directly
        template<typename T>
        bool Read(T& value) {
            return Read(&value, sizeof(T));
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
    };

}
