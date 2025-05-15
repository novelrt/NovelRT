#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsContext : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendContextType = typename GraphicsBackendTraits<TBackend>::ContextType;

    private:
        std::shared_ptr<BackendContextType> _implementation;
        size_t _index;

    public:

        GraphicsContext(std::shared_ptr<BackendContextType> implemenetation,
                        std::shared_ptr<GraphicsDevice<TBackend>> device,
                        size_t index) noexcept
            : GraphicsDeviceObject<TBackend>(device), _implementation(implemenetation), _index(index)
        {
        }

        virtual ~GraphicsContext() override = default;

        [[nodiscard]] std::shared_ptr<GraphicsFence<TBackend>> GetFence() const noexcept
        {
            return std::make_shared<GraphicsFence<TBackend>>(_implementation->GetFence(), GraphicsDeviceObject<TBackend>::GetDevice());
        }

        [[nodiscard]] inline size_t GetIndex() const noexcept
        {
            return _index;
        }

        [[nodiscard]] std::shared_ptr<GraphicsCmdList<TBackend>> BeginFrame()
        {
            return std::make_shared<GraphicsCmdList<TBackend>>(_implementation->BeginFrame(), std::static_pointer_cast<GraphicsContext<TBackend>>(GraphicsDeviceObject<TBackend>::shared_from_this()));
        }

        void EndFrame()
        {
            _implementation->EndFrame();
        }
    };
}
