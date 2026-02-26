#pragma once

#include "elfparser/common/Types.h"
#include <vector>

namespace ElfParser::Interface {
    class ISegment;
}

namespace ElfParser::Plugins::API {

    /**
     * @brief API for interacting with ELF Segments.
     */
    class ISegmentAPI {
    public:
        virtual ~ISegmentAPI() = default;

        /**
         * @brief Get a segment by index.
         */
        virtual Interface::ISegment* GetSegment(uint32_t index) = 0;

        /**
         * @brief Get all segments.
         */
        virtual std::vector<Interface::ISegment*> GetAllSegments() = 0;

        /**
         * @brief Create a new segment.
         */
        virtual Interface::ISegment* CreateSegment(uint32_t type, uint32_t flags) = 0;

        /**
         * @brief Remove a segment.
         */
        virtual Common::Result RemoveSegment(uint32_t index) = 0;
    };

}
