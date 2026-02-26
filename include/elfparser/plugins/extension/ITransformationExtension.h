#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/transform/ITransformation.h"
#include <memory>
#include <string>

namespace ElfParser::Plugins::Extensions {

    /**
     * @brief Extension point for custom ELF transformations.
     */
    class ITransformationExtension : public IExtension {
    public:
        std::string GetExtensionType() const override { return "TransformationExtension"; }

        /**
         * @brief Create a new transformation instance.
         * @return The transformation instance.
         */
        virtual std::unique_ptr<ElfParser::Transform::ITransformation> CreateTransformation() = 0;
    };

}
