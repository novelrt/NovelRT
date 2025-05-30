#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Exceptions/Exceptions.h>
#include <NovelRT/Windowing/Windowing.h>
#include <NovelRT/Input/IInputDevice.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/GraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Threading/Threading.h>
#include <memory>

namespace NovelRT::UI
{
    template<typename TBackend> class UIProvider : public std::enable_shared_from_this<UIProvider<TBackend>>
    {
    public:
        UIProvider() noexcept
        {
        }

        virtual void Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                                std::shared_ptr<Input::IInputDevice> inputDevice,
                                std::shared_ptr<Graphics::GraphicsDevice<TBackend>> graphicsDevice,
                                std::shared_ptr<Graphics::GraphicsMemoryAllocator<TBackend>> memoryAllocator,
                                bool debugMode) = 0;

        virtual void BeginFrame(float deltaTime) = 0;

        virtual void EndFrame() = 0;

        virtual void UploadToGPU(std::shared_ptr<Graphics::GraphicsCmdList<TBackend>> currentCmdList) = 0;

        virtual void Draw(std::shared_ptr<Graphics::GraphicsCmdList<TBackend>> currentCmdList) = 0;

        virtual ~UIProvider() = default;
    };
}
