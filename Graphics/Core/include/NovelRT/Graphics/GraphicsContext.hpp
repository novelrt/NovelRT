#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsDescriptorSet;
    template<typename TBackend>
    class GraphicsPipelineSignature;

    template<typename TBackend>
    class GraphicsContext : public GraphicsDeviceObject<TBackend>
    {
    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsContext<TBackend>> shared_from_this();
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsContext<TBackend>> shared_from_this() const;

        GraphicsContext() = delete;
        ~GraphicsContext() override = default;

        void BeginFrame();
        [[nodiscard]] std::shared_ptr<GraphicsCmdList<TBackend>> CreateCmdList(bool primary);
        void EndFrame();

        void RegisterDescriptorSetForFrame(std::weak_ptr<GraphicsPipelineSignature<TBackend>> signature,
                                           std::shared_ptr<GraphicsDescriptorSet<TBackend>> set);
    };
}
