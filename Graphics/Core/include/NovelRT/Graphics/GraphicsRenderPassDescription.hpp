#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/TexelFormat.hpp>
#include <vector>

namespace NovelRT::Graphics
{
    enum class LoadOp : uint8_t
    {
        Load,
        Clear,
        DontCare
    };

    enum class StoreOp : uint8_t
    {
        Store,
        DontCare
    };

    enum class ImageLayout : uint32_t
    {
        Undefined,
        Optimal,
        Present
    };

    struct GraphicsAttachmentDescription
    {
        TexelFormat texelFormat;
        LoadOp loadOp;
        StoreOp storeOp;
        LoadOp stencilLoadOp;
        StoreOp stencilStoreOp;
        ImageLayout initialLayout;
        ImageLayout finalLayout;
    };

    struct GraphicsSubpassDescription
    {
    };

    struct GraphicsSubpassDependencyDescription
    {
    };

    struct GraphicsRenderPassDescription
    {
        std::vector<GraphicsAttachmentDescription> attachmentDescriptions;
        // TODO: Figure out subpass support
        // std::vector<GraphicsSubpassDescription> subpassDescriptions;
        // std::vector<GraphicsSubpassDependencyDescription> subpassDependencies;
    };
}
