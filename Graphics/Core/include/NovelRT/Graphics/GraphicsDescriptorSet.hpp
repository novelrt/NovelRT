#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>

#include <NovelRT/Utilities/Span.hpp>

#include <memory>
#include <vector>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsResource;
    template<template<typename> typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion;

    template<typename TBackend>
    class GraphicsDescriptorSet : public GraphicsDeviceObject<TBackend>
    {
    public:
        GraphicsDescriptorSet() = delete;

        void AddMemoryRegionToInputs(
            const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>& region);

        void AddMemoryRegionsToInputs(
            NovelRT::Utilities::Span<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>>
                regions);

        void UpdateDescriptorSetData();
    };
}
