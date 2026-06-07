#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/RenderPassManager.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Ecs/UI/Components/UIButton.hpp>
#include <NovelRT/Ecs/UI/Components/UIClickEvent.hpp>
#include <NovelRT/Ecs/UI/Components/UISpriteButton.hpp>
#include <NovelRT/Ecs/UI/Components/UIText.hpp>
#include <NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp>
#include <NovelRT/Ecs/UI/UISystem.hpp>
#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <limits>
#include <memory>
#include <utility>

namespace NovelRT::Ecs::UI
{
    // template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    // class UISystem;

    template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    class EcsUIBuilder
    {
    private:
        std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>>
            _uiProvider;
        std::shared_ptr<NovelRT::Ecs::UI::UISystem<TGraphicsBackend, TInputBackend, TWindowingBackend>> _system;
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _gfxDevice;
        std::shared_ptr<NovelRT::Input::InputProvider<TInputBackend>> _inputProvider;
        std::shared_ptr<NovelRT::Windowing::WindowProvider<TWindowingBackend>> _wndProvider;
        std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<TGraphicsBackend>> _allocator;

        EcsUIBuilder()
        {
        }

        template<typename T1, typename T2, typename T3>
        friend EcsUIBuilder<T1, T2, T3>& AddUI(SystemSchedulerBuilder&);

    public:
        EcsUIBuilder(const EcsUIBuilder& other) = default;
        EcsUIBuilder& operator=(const EcsUIBuilder& other) = default;
        EcsUIBuilder(EcsUIBuilder&& other) = default;
        EcsUIBuilder& operator=(EcsUIBuilder&& other) = default;
        ~EcsUIBuilder() = default;

        EcsUIBuilder& WithUIProvider(
            std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>>&
                provider)
        {
            _uiProvider = provider;
            return *this;
        }

        EcsUIBuilder& WithUIProvider(
            std::shared_ptr<NovelRT::Windowing::WindowProvider<TWindowingBackend>>& windowProvider,
            std::shared_ptr<NovelRT::Input::InputProvider<TInputBackend>>& inputProvider,
            std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>>& graphicsDevice,
            std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<TGraphicsBackend>>& memoryAllocator,
            bool debugMode = false)
        {
            _uiProvider = std::make_shared<
                NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>>(
                windowProvider, inputProvider, graphicsDevice, memoryAllocator, debugMode);
            return *this;
        }

        EcsUIBuilder& WithDefaultUIProvider(bool debugMode = false)
        {
            _uiProvider = std::make_shared<
                NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>>(
                _wndProvider, _inputProvider, _gfxDevice, _allocator, debugMode);
            return *this;
        }

        EcsUIBuilder& WithUISystem(
            const std::shared_ptr<NovelRT::Ecs::UI::UISystem<TGraphicsBackend, TInputBackend, TWindowingBackend>>
                system)
        {
            _system = system;
            return *this;
        }

        EcsUIBuilder& WithGraphicsDevice(std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>>& device)
        {
            _gfxDevice = device;
            return *this;
        }

        EcsUIBuilder& WithGraphicsMemoryAllocator(
            std::shared_ptr<NovelRT::Graphics::GraphicsMemoryAllocator<TGraphicsBackend>>& allocator)
        {
            _allocator = allocator;
            return *this;
        }

        EcsUIBuilder& WithWindowProvider(
            std::shared_ptr<NovelRT::Windowing::WindowProvider<TWindowingBackend>>& provider)
        {
            _wndProvider = provider;
            return *this;
        }

        EcsUIBuilder& WithInputProvider(std::shared_ptr<NovelRT::Input::InputProvider<TInputBackend>>& provider)
        {
            _inputProvider = provider;
            return *this;
        }

        EcsUIBuilder& WithGraphicsBuilder(NovelRT::Ecs::Graphics::EcsGraphicsBuilder<TGraphicsBackend>& builder)
        {
            builder.ConfigureRenderPasses(
                [this](NovelRT::Ecs::Graphics::RenderPassManager<TGraphicsBackend>& renderPassManager)
                {
                    auto& id = _system->GetAssignedRenderPassId();
                    id = renderPassManager.RegisterRenderPass(_uiProvider->GetDedicatedRenderPass());
                });
            return *this;
        }

        EcsUIBuilder& WithDefaultUISystem()
        {
            // By default, we will upload the font data when creating the default UI system.
            // This is the user's responsibility if using a non-default UI system.
            auto gfxContext = _gfxDevice->CreateGraphicsContext();
            auto cmdList = gfxContext->CreateCmdList();
            _uiProvider->UploadFontData(cmdList);

            return WithUISystem(
                std::make_shared<NovelRT::Ecs::UI::UISystem<TGraphicsBackend, TInputBackend, TWindowingBackend>>(
                    _uiProvider, _gfxDevice));
        }

        EcsUIBuilder& AddFont(const std::string& name, const std::string& filePath)
        {
            _uiProvider->AddFontToUpload(name, filePath);
            return *this;
        }

        void operator()(SystemScheduler& scheduler)
        {
            auto& cache = scheduler.GetComponentCache();

            cache.RegisterComponentType(NovelRT::Ecs::UI::Components::UIWidgetContainer{},
                                        "NovelRT::Ecs::UI::UIWidgetContainer");
            cache.RegisterComponentType(NovelRT::Ecs::UI::Components::UIButton{}, "NovelRT::Ecs::UI::UIButton");
            cache.RegisterComponentType(NovelRT::Ecs::UI::Components::UIClickEvent{}, "NovelRT::Ecs::UI::UIClickEvent");
            cache.RegisterComponentType(NovelRT::Ecs::UI::Components::UIText{}, "NovelRT::Ecs::UI::UIText");

            unused(scheduler.RegisterSystem(_system));
        }
    };

    template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    EcsUIBuilder<TGraphicsBackend, TInputBackend, TWindowingBackend>& AddUI(SystemSchedulerBuilder& builder)
    {
        return builder.Configure(EcsUIBuilder<TGraphicsBackend, TInputBackend, TWindowingBackend>{});
    };
}
