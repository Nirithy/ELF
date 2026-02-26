#pragma once

#include <cstdint>
#include <type_traits>

namespace ElfParser::Utils {

    // Helper to check system endianness (runtime check, though usually constant)
    inline bool IsLittleEndian() {
        const int value = 1;
        const void* address = static_cast<const void*>(&value);
        const unsigned char* least_significant_byte = static_cast<const unsigned char*>(address);
        return *least_significant_byte == 1;
    }

    // Byte swapping functions
    inline uint16_t Swap16(uint16_t value) {
        return (value >> 8) | (value << 8);
    }

    inline uint32_t Swap32(uint32_t value) {
        return ((value >> 24) & 0x000000FF) |
               ((value >> 8)  & 0x0000FF00) |
               ((value << 8)  & 0x00FF0000) |
               ((value << 24) & 0xFF000000);
    }

    inline uint64_t Swap64(uint64_t value) {
        return ((value >> 56) & 0x00000000000000FF) |
               ((value >> 40) & 0x000000000000FF00) |
               ((value >> 24) & 0x0000000000FF0000) |
               ((value >> 8)  & 0x00000000FF000000) |
               ((value << 8)  & 0x000000FF00000000) |
               ((value << 24) & 0x0000FF0000000000) |
               ((value << 40) & 0x00FF000000000000) |
               ((value << 56) & 0xFF00000000000000);
    }

    // Template wrapper for generic swapping
    template <typename T>
    inline T Swap(T value) {
        static_assert(std::is_arithmetic<T>::value, "Swap only supports arithmetic types");
        if constexpr (sizeof(T) == 1) {
            return value;
        } else if constexpr (sizeof(T) == 2) {
            return static_cast<T>(Swap16(static_cast<uint16_t>(value)));
        } else if constexpr (sizeof(T) == 4) {
            return static_cast<T>(Swap32(static_cast<uint32_t>(value)));
        } else if constexpr (sizeof(T) == 8) {
            return static_cast<T>(Swap64(static_cast<uint64_t>(value)));
        } else {
            return value; // Should probably assert or error for weird sizes
        }
    }

}
