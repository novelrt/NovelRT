#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/Camera.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/Sprite.hpp>
#include <NovelRT/Ecs/Graphics/Components/TrackedSemaphore.hpp>
#include <NovelRT/Ecs/Graphics/Components/Viewport.hpp>
#include <NovelRT/Ecs/Graphics/SpriteRendererSystem.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>

#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <limits>
#include <memory>
#include <utility>

namespace NovelRT::Ecs::Graphics
{
    template<typename TGraphicsBackend>
    class RenderOrchestratorSystem;

    template<typename TGraphicsBackend>
    class RenderPassManager;

    template<typename TGraphicsBackend>
    class EcsGraphicsBuilder
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;
        std::shared_ptr<RenderOrchestratorSystem<TGraphicsBackend>> _orchestrator;
        std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>> _context;
        std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<TGraphicsBackend>> _memoryAllocator;
        std::shared_ptr<NovelRT::ResourceManagement::Desktop::DesktopResourceLoader> _resourceLoader;
        std::shared_ptr<SpriteRendererSystem<TGraphicsBackend>> _defaultSpriteRenderer;

        Components::BuiltCommandList<TGraphicsBackend> _defaultBuiltCommandListComponent;
        Components::RenderPass<TGraphicsBackend> _defaultRenderPassComponent;
        Components::TrackedSemaphore<TGraphicsBackend> _defaultTrackedSemaphoreComponent;
        Components::Sprite _defaultSpriteComponent;
        Components::Camera _defaultCameraComponent;
        Components::Viewport _defaultViewportComponent;

        RenderPassManager<TGraphicsBackend> _passManager;

        NovelRT::Graphics::RGBAColour _backgroundColour{0, 0, 0, 255};

        EcsGraphicsBuilder()
            : _defaultBuiltCommandListComponent{nullptr},
              _defaultRenderPassComponent{std::numeric_limits<Components::RenderPassId>::max(), nullptr},
              _defaultTrackedSemaphoreComponent{nullptr, 0},
              _defaultSpriteComponent{},
              _defaultCameraComponent{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, false},
              _defaultViewportComponent{0.0f, 0.0f, 0.0f, 0.0f}
        {
        }

        template<typename T>
        friend EcsGraphicsBuilder<T>& AddGraphics(SystemSchedulerBuilder&);

    public:
        EcsGraphicsBuilder(const EcsGraphicsBuilder& other) = delete;
        EcsGraphicsBuilder& operator=(const EcsGraphicsBuilder& other) = delete;
        EcsGraphicsBuilder(EcsGraphicsBuilder&& other) = default;
        EcsGraphicsBuilder& operator=(EcsGraphicsBuilder&& other) = default;
        ~EcsGraphicsBuilder() = default;

        EcsGraphicsBuilder& WithGraphicsDevice(
            std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>>& device)
        {
            _graphicsDevice = device;
            return *this;
        }

        EcsGraphicsBuilder& WithResourceLoader(
            std::shared_ptr<NovelRT::ResourceManagement::Desktop::DesktopResourceLoader>& resourceLoader)
        {
            _resourceLoader = resourceLoader;
            return *this;
        }

        EcsGraphicsBuilder& WithMemoryAllocator(
             std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>>& memoryAllocator)
        {
            _memoryAllocator = memoryAllocator;
            return *this;
        }


        EcsGraphicsBuilder& WithSurfaceContext(
            std::shared_ptr<NovelRT::Graphics::GraphicsSurfaceContext<TGraphicsBackend>>& context)
        {
            _context = context;
            return *this;
        }

        EcsGraphicsBuilder& ConfigureRenderPasses(std::function<void(RenderPassManager<TGraphicsBackend>&)> configure)
        {
            configure(_passManager);
            return *this;
        }

        EcsGraphicsBuilder& WithDefaultBuiltCommandListComponent(
            const Components::BuiltCommandList<TGraphicsBackend>& defaultBuiltCommandListComponent)
        {
            _defaultBuiltCommandListComponent = defaultBuiltCommandListComponent;
            return *this;
        }

        EcsGraphicsBuilder& WithDefaultRenderPassComponent(
            const Components::RenderPass<TGraphicsBackend>& defaultRenderPassComponent)
        {
            _defaultRenderPassComponent = defaultRenderPassComponent;
            return *this;
        }

        EcsGraphicsBuilder& WithOrchestrator(
            const std::shared_ptr<RenderOrchestratorSystem<TGraphicsBackend>>& orchestrator)
        {
            _orchestrator = orchestrator;
            return *this;
        }

        EcsGraphicsBuilder& WithDefaultBackgroundColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            _backgroundColour = NovelRT::Graphics::RGBAColour(r, g, b, a);
            return *this;
        }

        EcsGraphicsBuilder& WithDefaultOrchestrator()
        {
            auto orchestrator =
                std::make_shared<RenderOrchestratorSystem<TGraphicsBackend>>(_graphicsDevice, _context, _passManager);
            orchestrator->SetBackgroundColour(_backgroundColour);
            return WithOrchestrator(orchestrator);
        }

        void operator()(SystemScheduler& scheduler)
        {
            // TODO: add systems and components for rendering
            auto& cache = scheduler.GetComponentCache();

            cache.RegisterComponentType(_defaultBuiltCommandListComponent, "NovelRT::Ecs::Graphics::BuiltCommandList");
            cache.RegisterComponentType(_defaultRenderPassComponent, "NovelRT::Ecs::Graphics::RenderPass");
            cache.RegisterComponentType(_defaultTrackedSemaphoreComponent, "NovelRT::Ecs::Graphics::TrackedSemaphore");
            cache.RegisterComponentType(_defaultSpriteComponent, "NovelRT::Ecs::Graphics::Sprite");
            cache.RegisterComponentType(_defaultCameraComponent, "NovelRT::Ecs::Graphics::Camera");
            cache.RegisterComponentType(_defaultViewportComponent, "NovelRT::Ecs::Graphics::Viewport");

            if(_defaultSpriteRenderer != nullptr) {
                unused(scheduler.RegisterSystem(_defaultSpriteRenderer));
            }
            unused(scheduler.RegisterSystemDependsOnAll(_orchestrator));
        }
        
        EcsGraphicsBuilder& WithDefaultSpriteRendering() 
        {
           typename SpriteRendererSystem<TGraphicsBackend>::SpritePass pass{};

            ConfigureRenderPasses(
                [&](RenderPassManager<TGraphicsBackend>& renderPassManager)
                {
                    NovelRT::Graphics::GraphicsRenderPassDescription passDesc{};
                    NovelRT::Graphics::GraphicsAttachmentDescription attachmentDesc{};

                    attachmentDesc.texelFormat = _graphicsDevice->GetSwapchain()->GetFormat();
                    attachmentDesc.loadOp = NovelRT::Graphics::LoadOp::Clear;
                    attachmentDesc.storeOp = NovelRT::Graphics::StoreOp::Store;
                    attachmentDesc.initialLayout = NovelRT::Graphics::ImageLayout::Undefined;
                    attachmentDesc.finalLayout = NovelRT::Graphics::ImageLayout::Present;

                    passDesc.attachmentDescriptions.push_back(attachmentDesc);
                    pass.RenderPass = _graphicsDevice->CreateRenderPass(passDesc);
                    pass.RenderPassId = renderPassManager.RegisterRenderPass(pass.RenderPass);
                });
            
                if(_graphicsDevice == nullptr) 
                {
                    throw std::invalid_argument("_resourceLoader is a nullPtr. Call WithGraphicsDevice to set it");
                } 
                else if( _resourceLoader == nullptr) 
                {
                    throw std::invalid_argument("_resourceLoader is a nullPtr. Call WithResourceLoader to set it");
                } 
                else if(_memoryAllocator == nullptr) 
                {
                    throw std::invalid_argument("_memoryAllocator is a nullPtr. Call WithMemoryAllocator to set it");
                } 
                else if (_context == nullptr) 
                {
                    throw std::invalid_argument("_context is a nullPtr. Call WithSurfaceContext to set it");
                }
                else {
                    _defaultSpriteRenderer = std::make_shared<SpriteRendererSystem<TGraphicsBackend>>( 
                    _graphicsDevice, pass, _resourceLoader, _memoryAllocator, _context);
                }

                return *this;
        }
    };

    template<typename TGraphicsBackend>
    EcsGraphicsBuilder<TGraphicsBackend>& AddGraphics(SystemSchedulerBuilder& builder)
    {
        return builder.Configure(EcsGraphicsBuilder<TGraphicsBackend>{});
    };
}
