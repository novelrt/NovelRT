#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsContext : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendContextType = typename GraphicsBackendTraits<TBackend>::ContextType;
        using BackendFenceType = typename GraphicsBackendTraits<TBackend>::FenceType;

    private:
        std::unique_ptr<BackendContextType> _implementation;
        size_t _index;

        mutable Utilities::Lazy<std::shared_ptr<GraphicsFence<TBackend>>> _fence;
    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsContext<TBackend>> shared_from_this()
        {
            return std::static_pointer_cast<GraphicsContext<TBackend>>(GraphicsDeviceObject<TBackend>::shared_from_this());
        }

        GraphicsContext(std::unique_ptr<BackendContextType> implemenetation,
                        std::shared_ptr<GraphicsDevice<TBackend>> device,
                        size_t index) noexcept
            : GraphicsDeviceObject<TBackend>(std::move(device))
            , _implementation(std::move(implemenetation))
            , _index(index)
            , _fence([this](){
                return std::make_shared<GraphicsFence<TBackend>>(std::unique_ptr<BackendFenceType>{_implementation->GetFence()}, GraphicsDeviceObject<TBackend>::GetDevice());
            })
        {
        }

        virtual ~GraphicsContext() override = default;

        [[nodiscard]] BackendContextType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }

        [[nodiscard]] GraphicsFence<TBackend>* GetFence() const noexcept
        {
            return _fence.Get().get();
        }

        [[nodiscard]] size_t GetIndex() const noexcept
        {
            return _index;
        }

        [[nodiscard]] std::shared_ptr<GraphicsCmdList<TBackend>> BeginFrame()
        {
            return std::make_shared<GraphicsCmdList<TBackend>>(
                _implementation->BeginFrame(),
                this->shared_from_this());
        }

        void RegisterDescriptorSetForFrame(std::shared_ptr<GraphicsPipelineSignature<TBackend>> signature, std::shared_ptr<GraphicsDescriptorSet<TBackend>> set)
        {
            _implementation->RegisterDescriptorSetForFrame(signature->GetImplementation(), set->GetImplementation());
        }

        void EndFrame()
        {
            _implementation->EndFrame();
        }
    };
}
