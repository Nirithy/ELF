#include "elfparser/io/BinaryReader.h"
#include "elfparser/utils/Logger.h"
#include <iostream>

namespace ElfParser::IO {

    BinaryReader::BinaryReader(const std::string& filepath)
        : m_filepath(filepath), m_fileSize(0) {}

    BinaryReader::~BinaryReader() {
        Close();
    }

    bool BinaryReader::Open() {
        m_stream.open(m_filepath, std::ios::binary | std::ios::ate);
        if (!m_stream.is_open()) {
            Utils::Logger::Error("Failed to open file: " + m_filepath);
            return false;
        }

        m_fileSize = m_stream.tellg();
        m_stream.seekg(0, std::ios::beg);
        return true;
    }

    void BinaryReader::Close() {
        if (m_stream.is_open()) {
            m_stream.close();
        }
    }

    bool BinaryReader::Read(void* buffer, std::streamsize size) {
        if (!m_stream.is_open()) {
            Utils::Logger::Error("Attempted to read from closed file.");
            return false;
        }

        m_stream.read(reinterpret_cast<char*>(buffer), size);

        // Ensure we read the requested amount
        if (m_stream.gcount() != size) {
            Utils::Logger::Error("Read incomplete: expected " + std::to_string(size) +
                                 ", got " + std::to_string(m_stream.gcount()));
            return false;
        }
        return true;
    }

    bool BinaryReader::Seek(std::streampos pos) {
        if (!m_stream.is_open()) {
            Utils::Logger::Error("Attempted to seek in closed file.");
            return false;
        }

        // Basic bounds check
        // streampos comparison is tricky, convert to streamoff
        if (static_cast<std::streamoff>(pos) > static_cast<std::streamoff>(m_fileSize)) {
             Utils::Logger::Error("Seek position " + std::to_string(static_cast<std::streamoff>(pos)) +
                                  " is out of bounds (Size: " + std::to_string(m_fileSize) + ").");
             return false;
        }

        m_stream.seekg(pos);
        if (m_stream.fail()) {
            Utils::Logger::Error("Seek operation failed.");
            return false;
        }
        return true;
    }

    std::streampos BinaryReader::Tell() {
        if (!m_stream.is_open()) return 0;
        return m_stream.tellg();
    }

    std::streamsize BinaryReader::GetSize() {
        return m_fileSize;
    }

    bool BinaryReader::ReadString(std::string& str, size_t maxLength) {
        str.clear();
        char c;
        for (size_t i = 0; i < maxLength; ++i) {
            if (!Read(&c, 1)) return false;
            if (c == '\0') break;
            str += c;
        }
        return true;
    }

}
