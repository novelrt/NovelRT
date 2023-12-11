#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>

namespace NovelRT::Graphics
{
    class GraphicsContext : public GraphicsDeviceObject
    {
    private:
        size_t _index;

    public:
        GraphicsContext(std::shared_ptr<GraphicsDevice> device, size_t index) noexcept
            : GraphicsDeviceObject(device), _index(index)
        {
        }
        
        virtual ~GraphicsContext() override = default;

        [[nodiscard]] virtual std::shared_ptr<GraphicsFence> GetFence() const noexcept = 0;

        [[nodiscard]] inline size_t GetIndex() const noexcept
        {
            return _index;
        }

        virtual void BeginDrawing(RGBAColour backgroundColour) = 0;
        virtual void BeginFrame() = 0;

        virtual void EndDrawing() = 0;
        virtual void EndFrame() = 0;
    };
}
