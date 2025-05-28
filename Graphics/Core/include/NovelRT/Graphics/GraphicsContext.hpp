#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsDescriptorSet;
    template<typename TBackend> class GraphicsPipelineSignature;

    template<typename TBackend> class GraphicsContext : public GraphicsDeviceObject<TBackend>
    {
    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsContext<TBackend>> shared_from_this();

        GraphicsContext() = delete;
        ~GraphicsContext() override = default;

        [[nodiscard]] std::shared_ptr<GraphicsFence<TBackend>> GetFence() const noexcept;

        [[nodiscard]] size_t GetIndex() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsCmdList<TBackend>> BeginFrame();
        void EndFrame();

        void RegisterDescriptorSetForFrame(std::weak_ptr<GraphicsPipelineSignature<TBackend>> signature,
                                           std::shared_ptr<GraphicsDescriptorSet<TBackend>> set);
    };
}
