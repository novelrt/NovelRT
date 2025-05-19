#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>
#include <vector>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsBuffer;
    template<typename TBackend> class GraphicsPipeline;
    template<typename TBackend> class GraphicsTexture;
    template<typename TBackend> struct GraphicsBackendTraits;
    template<typename TBackend> class GraphicsResource;

    template<typename TBackend> class GraphicsDescriptorSet : std::enable_shared_from_this<GraphicsDescriptorSet<TBackend>>
    {
    public:
        using BackendDescriptorSetType = typename GraphicsBackendTraits<TBackend>::DescriptorSetType;

    private:
        std::unique_ptr<BackendDescriptorSetType> _implementation;
        std::shared_ptr<GraphicsPipeline<TBackend>> _pipeline;

        using BackendMemoryRegionBaseType = typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<typename GraphicsBackendTraits<TBackend>::ResourceType>;

    public:
        explicit GraphicsDescriptorSet(std::unique_ptr<BackendDescriptorSetType> implementation,
                                       std::shared_ptr<GraphicsPipeline<TBackend>> targetPipeline) noexcept
            : _implementation(std::move(implementation))
            , _pipeline(std::move(targetPipeline))
        {
        }

        [[nodiscard]] BackendDescriptorSetType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }

        void AddMemoryRegionToInputs(const GraphicsResourceMemoryRegion<GraphicsResource, TBackend>* region)
        {
            _implementation->AddMemoryRegionToInputs(region->GetImplementation());
        }

        void AddMemoryRegionsToInputs(NovelRT::Utilities::Span<const GraphicsResourceMemoryRegion<GraphicsResource, TBackend>*> regions)
        {
            std::vector<const BackendMemoryRegionBaseType*> args{};
            args.resize(regions.size());
            std::transform(regions.begin(), regions.end(), args.begin(), [&](auto x){ return x->GetImplementation(); });

            _implementation->AddMemoryRegionsToInputs(args);
        }

        void UpdateDescriptorSetData()
        {
            _implementation->UpdateDescriptorSetData();
        }
    };
}
