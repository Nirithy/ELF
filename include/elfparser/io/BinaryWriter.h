#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <type_traits>
#include "elfparser/common/Types.h"
#include "elfparser/utils/Endian.h"

namespace ElfParser::IO {

    class BinaryWriter {
    public:
        explicit BinaryWriter(const std::string& filepath);
        ~BinaryWriter();

        // Delete copy/move to avoid issues with fstream
        BinaryWriter(const BinaryWriter&) = delete;
        BinaryWriter& operator=(const BinaryWriter&) = delete;

        Common::Result Open();
        void Close();

        // Set the endianness of the output file.
        // If it differs from the host system, Write<T> will swap bytes.
        void SetLittleEndian(bool isLittleEndian);

        // Check if swapping is enabled
        bool ShouldSwap() const { return m_shouldSwap; }

        // Write raw bytes
        Common::Result Write(const void* buffer, std::streamsize size);

        // Template to write primitive types directly with automatic endian swapping
        template<typename T>
        Common::Result Write(T value) {
            if (m_shouldSwap) {
                if constexpr (std::is_arithmetic<T>::value) {
                    value = Utils::Swap(value);
                }
            }
            return Write(&value, sizeof(T));
        }

        // Write a vector of primitives
        template<typename T>
        Common::Result Write(const std::vector<T>& values) {
            for (const auto& val : values) {
                auto res = Write(val);
                if (!res.IsOk()) return res;
            }
            return Common::Result::Ok();
        }

        // Seek to an absolute position
        Common::Result Seek(std::streampos pos);

        // Get current position
        std::streampos Tell();

        // Write padding bytes (zeros)
        Common::Result WritePadding(size_t count);

    private:
        std::string m_filepath;
        std::ofstream m_stream;
        bool m_shouldSwap = false;
    };

}
