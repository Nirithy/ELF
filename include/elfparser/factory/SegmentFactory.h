#pragma once

#include <memory>
#include "elfparser/interface/ISegment.h"
#include "elfparser/model/enums/ElfSegmentType.h"

namespace ElfParser::Factory {

    class SegmentFactory {
    public:
        /**
         * @brief Creates a new Segment instance.
         * @param type The type of the segment.
         * @return A unique pointer to the created segment.
         */
        static std::unique_ptr<Interface::ISegment> CreateSegment(
            Model::ElfSegmentType type = Model::ElfSegmentType::Null
        );
    };

}
