#pragma once

#include <cstdint>
#include <string>

namespace ElfParser::Common {

    // Define standard types for clarity
    using Byte = uint8_t;
    using Address = uint64_t;
    using Offset = uint64_t;
    using Size = uint64_t;

    // Error codes for the parser
    enum class StatusCode {
        Ok,
        Error,
        FileNotFound,
        InvalidFormat,
        OutOfBounds,
        ReadError,
        WriteError,
        NotImplemented
    };

    // A simple Result structure to propagate errors
    struct Result {
        StatusCode code;
        std::string message;

        static Result Ok() {
            return {StatusCode::Ok, ""};
        }

        static Result Fail(StatusCode code, const std::string& msg) {
            return {code, msg};
        }

        bool IsOk() const {
            return code == StatusCode::Ok;
        }
    };

}
