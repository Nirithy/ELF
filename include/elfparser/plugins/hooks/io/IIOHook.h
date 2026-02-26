#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/common/Types.h"
#include <vector>
#include <cstdint>

namespace ElfParser::Plugins::Hooks {

    class IIOHook : public Extensions::IExtension {
    public:
        virtual ~IIOHook() = default;

        virtual void OnRead(uint64_t offset, uint64_t size) = 0;
        virtual void OnWrite(uint64_t offset, const std::vector<uint8_t>& data) = 0;
    };
}
