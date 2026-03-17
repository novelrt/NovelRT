#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Utilities/Span.hpp>


namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsRenderTarget : public GraphicsDeviceObject<TBackend>
    {
    public:
        GraphicsRenderTarget() = delete;
        ~GraphicsRenderTarget() noexcept final = delete;;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<TBackend>> GetDevice() const noexcept;
    };
}
