#include "elfparser/factory/SegmentFactory.h"
#include "elfparser/model/impl/SegmentImpl.h"

namespace ElfParser::Factory {

    std::unique_ptr<Interface::ISegment> SegmentFactory::CreateSegment(
        Model::ElfSegmentType type
    ) {
        return std::make_unique<Model::SegmentImpl>(type);
    }

}
