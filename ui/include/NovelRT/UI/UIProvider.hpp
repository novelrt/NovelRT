
#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Exceptions/Exceptions.h>
#include <NovelRT/Windowing/Windowing.h>
#include <NovelRT/Input/IInputDevice.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <memory>

using namespace NovelRT::Graphics::Vulkan;

namespace NovelRT::UI
{
    class UIProvider : public std::enable_shared_from_this<UIProvider>
    {
    public:
        UIProvider() noexcept
        {
        }

        virtual void Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                                std::shared_ptr<Input::IInputDevice> inputDevice,
                                std::shared_ptr<Graphics::GraphicsDevice<VulkanGraphicsBackend>> graphicsDevice) = 0;

        virtual void BeginFrame(double deltaTime) = 0;

        virtual void EndFrame() = 0;

        virtual ~UIProvider() = default;
    };
}
