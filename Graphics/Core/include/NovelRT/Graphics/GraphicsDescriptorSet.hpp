#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Utilities/Misc.h>
#include <memory>
#include <vector>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsBuffer;
    template<typename TBackend> class GraphicsPipeline;
    template<typename TBackend> class GraphicsTexture;
    template<typename TBackend> struct GraphicsBackendTraits;

    //TODO: FIX BASE TYPING
    template<typename TBackend> class GraphicsDescriptorSet
    {
    public:
        using BackendDescriptorSetType = typename GraphicsBackendTraits<TBackend>::DescriptorSetType;

    private:
        std::shared_ptr<BackendDescriptorSetType> _implementation;
        std::shared_ptr<GraphicsPipeline<TBackend>> _pipeline;

        using BackendMemoryRegionBaseType = typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<typename GraphicsBackendTraits<TBackend>::ResourceType>;

    public:
        explicit GraphicsDescriptorSet(std::shared_ptr<BackendDescriptorSetType> implementation,
                                       std::shared_ptr<GraphicsPipeline<TBackend>> targetPipeline) noexcept
            : _implementation(implementation), _pipeline(targetPipeline)
        {
        }

        [[nodiscard]] std::shared_ptr<BackendDescriptorSetType> GetImplementation() const noexcept
        {
            return _implementation;
        }

        void AddMemoryRegionToInputs(std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>> region)
        {
            _implementation->AddMemoryRegionToInputs(region->GetImplementation());
        }

        void AddMemoryRegionsToInputs(NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>> regions)
        {
            std::vector<std::shared_ptr<BackendMemoryRegionBaseType>> args{};
            args.resize(regions.size());
            std::transform(regions.begin(), regions.end(), args.begin(), [&](auto x){ return x->GetImplementation(); });

            _implementation->AddMemoryRegionsToInputs(args);
        }
    };
}
