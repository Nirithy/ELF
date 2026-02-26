#include "elfparser/io/BinaryWriter.h"
#include "elfparser/utils/Logger.h"
#include <iostream>

namespace ElfParser::IO {

    BinaryWriter::BinaryWriter(const std::string& filepath)
        : m_filepath(filepath), m_shouldSwap(false) {}

    BinaryWriter::~BinaryWriter() {
        Close();
    }

    Common::Result BinaryWriter::Open() {
        m_stream.open(m_filepath, std::ios::binary | std::ios::trunc | std::ios::out);
        if (!m_stream.is_open()) {
            return Common::Result::Fail(Common::StatusCode::WriteError, "Failed to open file for writing: " + m_filepath);
        }
        return Common::Result::Ok();
    }

    void BinaryWriter::Close() {
        if (m_stream.is_open()) {
            m_stream.close();
        }
    }

    void BinaryWriter::SetLittleEndian(bool isLittleEndian) {
        m_shouldSwap = (isLittleEndian != Utils::IsLittleEndian());
    }

    Common::Result BinaryWriter::Write(const void* buffer, std::streamsize size) {
        if (!m_stream.is_open()) {
            return Common::Result::Fail(Common::StatusCode::WriteError, "Attempted to write to closed file.");
        }

        m_stream.write(reinterpret_cast<const char*>(buffer), size);
        if (m_stream.fail()) {
             return Common::Result::Fail(Common::StatusCode::WriteError, "Write operation failed.");
        }
        return Common::Result::Ok();
    }

    Common::Result BinaryWriter::Seek(std::streampos pos) {
        if (!m_stream.is_open()) {
            return Common::Result::Fail(Common::StatusCode::WriteError, "Attempted to seek in closed file.");
        }

        m_stream.seekp(pos);
        if (m_stream.fail()) {
            return Common::Result::Fail(Common::StatusCode::WriteError, "Seek operation failed.");
        }
        return Common::Result::Ok();
    }

    std::streampos BinaryWriter::Tell() {
        if (!m_stream.is_open()) return 0;
        return m_stream.tellp();
    }

    Common::Result BinaryWriter::WritePadding(size_t count) {
        if (count == 0) return Common::Result::Ok();
        std::vector<char> zeros(count, 0);
        return Write(zeros.data(), count);
    }

}
