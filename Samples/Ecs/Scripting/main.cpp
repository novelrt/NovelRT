// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Ecs/Components/TransformComponent.hpp>

#include <NovelRT/Ecs/Graphics/Components/Camera.hpp>
#include <NovelRT/Ecs/Graphics/Components/Viewport.hpp>
#include <NovelRT/Ecs/Graphics/EcsGraphicsBuilder.hpp>
#include <NovelRT/Ecs/Graphics/RenderOrchestratorSystem.hpp>
#include <NovelRT/Ecs/Graphics/RenderPassManager.hpp>
#include <NovelRT/Ecs/Graphics/SpriteRendererSystem.hpp>

#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/DecisionTreeLoadRequest.hpp>
#include <NovelRT/Ecs/Scripting/Components/LoadedDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeLoadingSystem.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStateManager.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp>
#include <NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp>
#include <NovelRT/Ecs/Scripting/StepSystems/BranchStepSystem.hpp>
#include <NovelRT/Ecs/Scripting/StepSystems/SpokenLineStepSystem.hpp>

#include <NovelRT/Ecs/Scripting/Graphics/PoseToSpriteTranslationSystem.hpp>
#include <NovelRT/Ecs/Scripting/UI/BranchTranslationSystem.hpp>
#include <NovelRT/Ecs/Scripting/UI/SpokenLineTranslationSystem.hpp>

#include <NovelRT/Ecs/UI/Components/UIButton.hpp>
#include <NovelRT/Ecs/UI/Components/UIClickEvent.hpp>
#include <NovelRT/Ecs/UI/Components/UIElement.hpp>
#include <NovelRT/Ecs/UI/Components/UIText.hpp>
#include <NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp>
#include <NovelRT/Ecs/UI/EcsUIBuilder.hpp>
#include <NovelRT/Ecs/UI/UIComponentType.hpp>
#include <NovelRT/Ecs/UI/UISystem.hpp>

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>

#include <NovelRT/Input/Glfw/GlfwInputProvider.hpp>

#include <NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/Statuses/Branch.hpp>
#include <NovelRT/Scripting/Statuses/SpokenLine.hpp>

#include <NovelRT/Timing/StepTimer.hpp>

#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

#include <memory>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Graphics;
using namespace NovelRT::Ecs::Scripting;
using namespace NovelRT::Ecs::Scripting::Graphics;
using namespace NovelRT::Ecs::Scripting::UI;
using namespace NovelRT::Ecs::UI;
using namespace NovelRT::Graphics;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Input;
using namespace NovelRT::Maths;
using namespace NovelRT::ResourceManagement;
using namespace NovelRT::ResourceManagement::Desktop;
using namespace NovelRT::Scripting;
using namespace NovelRT::Timing;
using namespace NovelRT::Utilities;
using namespace NovelRT::UI::ImGui;
using namespace NovelRT::Windowing;

class InitialisationSystem : public IEcsSystem
{
private:
    bool _initialized = false;

    std::shared_ptr<ResourceLoader> _resourceLoader;
    std::shared_ptr<ScriptManager> _scriptManager;

public:
    InitialisationSystem(const std::shared_ptr<ResourceLoader>& resourceLoader,
                         const std::shared_ptr<ScriptManager>& scriptManager)
        : _resourceLoader(resourceLoader), _scriptManager(scriptManager)
    {
    }

    void Update(NovelRT::Timing::Timestamp /*delta*/, Catalogue catalogue) final
    {
        if (_initialized)
        {
            return;
        }

        _initialized = true;

        auto [cameras, viewports, transforms, loadRequests] =
            catalogue.GetComponentViews<NovelRT::Ecs::Graphics::Components::Camera,
                                        NovelRT::Ecs::Graphics::Components::Viewport,
                                        NovelRT::Ecs::Components::TransformComponent,
                                        NovelRT::Ecs::Scripting::Components::DecisionTreeLoadRequest>();
        auto cameraEntity = catalogue.CreateEntity();

        transforms.PushComponentUpdateInstruction(
            cameraEntity, NovelRT::Ecs::Components::TransformComponent{.position = GeoVector2F{0.0f, 0.0f},
                                                                       .scale = GeoVector2F{1.0f, 1.0f},
                                                                       .rotationInRadians = 0.0f});

        cameras.PushComponentUpdateInstruction(
            cameraEntity, NovelRT::Ecs::Graphics::Components::Camera{.left = -1.0f,
                                                                     .right = 1.0f,
                                                                     .bottom = 1.0f,
                                                                     .top = -1.0f,
                                                                     .nearPlane = 0.0f,
                                                                     .farPlane = 1.0f,
                                                                     .referenceResolutionWidth = 1280,
                                                                     .referenceResolutionHeight = 720,

                                                                     .isScreenSpace = true});

        viewports.PushComponentUpdateInstruction(
            cameraEntity, NovelRT::Ecs::Graphics::Components::Viewport{.width = 1280, .height = 720});

        auto scriptEntity = catalogue.CreateEntity();
        auto scriptAsset = _resourceLoader->TryGetAssetIdBasedOnFilePath("Scripts/Sample.lua");

        if (!scriptAsset.has_value())
            throw NovelRT::Exceptions::InitialisationFailureException{"Failed to find script asset"};

        loadRequests.PushComponentUpdateInstruction(
            scriptEntity, NovelRT::Ecs::Scripting::Components::DecisionTreeLoadRequest{.assetId = scriptAsset.value()});
    }
};

class BeginDecisionTreeSystem : public DecisionTreeStepSystem
{
public:
    BeginDecisionTreeSystem(DecisionTreeStateManager& stateManager) : DecisionTreeStepSystem(stateManager)
    {
    }

    void Update(NovelRT::Timing::Timestamp /*delta*/, Catalogue catalogue) final
    {
        auto [loadedTrees, activeTrees] =
            catalogue.GetComponentViews<NovelRT::Ecs::Scripting::Components::LoadedDecisionTree,
                                        NovelRT::Ecs::Scripting::Components::ActiveDecisionTree>();

        for (const auto& [entity, tree] : loadedTrees)
        {
            if (activeTrees.HasComponent(entity))
            {
                continue;
            }

            Continue(catalogue, entity, (*tree.decisionTree)->Begin());
        }
    }
};

class ViewportUpdateSystem : public IEcsSystem
{
private:
    NovelRT::Maths::GeoVector2F _size{};
    bool _changedSize = false;

public:
    ViewportUpdateSystem(std::shared_ptr<WindowProvider<NovelRT::Windowing::Glfw::GlfwWindowingBackend>> provider)
    {
        provider->SizeChanged += [this](auto eventArgs)
        {
            _size = eventArgs;
            _changedSize = true;
        };
    }

    void Update(NovelRT::Timing::Timestamp /*delta*/, Catalogue catalogue) final
    {
        if (!_changedSize)
        {
            return;
        }

        _changedSize = false;

        auto [viewports] = catalogue.GetComponentViews<NovelRT::Ecs::Graphics::Components::Viewport>();

        for (auto [entity, _] : viewports)
        {
            viewports.PushComponentUpdateInstruction(
                entity, NovelRT::Ecs::Graphics::Components::Viewport{.width = _size.x, .height = _size.y});
        }
    }
};

int main()
{
    SystemSchedulerBuilder builder{};
    SpriteRendererSystem<VulkanGraphicsBackend>::SpritePass passData{};

    auto wndProvider = std::make_shared<WindowProvider<NovelRT::Windowing::Glfw::GlfwWindowingBackend>>(
        NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F{1280, 720});

    auto inputProvider = std::make_shared<InputProvider<NovelRT::Input::Glfw::GlfwInputBackend>>(wndProvider);

    auto scriptManager = std::make_shared<ScriptManager>();
    auto resourceLoader = std::make_shared<DesktopResourceLoader>();

    auto gfxProvider = wndProvider->CreateGraphicsProvider<VulkanGraphicsBackend>(true);
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider, gfxSurfaceContext);
    auto gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext);
    auto memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(gfxDevice, gfxProvider);

    resourceLoader->InitAssetDatabase();

    auto defaultSpriteRenderer = std::make_shared<SpriteRendererSystem<VulkanGraphicsBackend>>(
        gfxDevice, passData, resourceLoader, memoryAllocator, gfxSurfaceContext);

    AddDefaults(builder);

    auto& gfx = AddGraphics<Vulkan::VulkanGraphicsBackend>(builder)
                    .WithGraphicsDevice(gfxDevice)
                    .WithSurfaceContext(gfxSurfaceContext)
                    .ConfigureRenderPasses(
                        [gfxDevice, &passData](auto& manager)
                        {
                            GraphicsRenderPassDescription passDesc{};
                            GraphicsAttachmentDescription attachmentDesc{};

                            attachmentDesc.texelFormat = gfxDevice->GetSwapchain()->GetFormat();
                            attachmentDesc.loadOp = LoadOp::Load;
                            attachmentDesc.storeOp = StoreOp::Store;
                            attachmentDesc.initialLayout = ImageLayout::Present;
                            attachmentDesc.finalLayout = ImageLayout::Present;

                            passDesc.attachmentDescriptions.push_back(attachmentDesc);
                            passData.RenderPass = gfxDevice->CreateRenderPass(passDesc);
                            passData.RenderPassId = manager.RegisterRenderPass(passData.RenderPass);
                        })
                    .WithDefaultBackgroundColour(0, 0, 0, 255);

    AddScripting(builder)
        .WithScriptManager(scriptManager)
        .WithDecisionTreeLoadingSystem([&resourceLoader](auto& manager)
                                       { return std::make_shared<DecisionTreeLoadingSystem>(manager, resourceLoader); })
        .RegisterStepSystem([](auto& manager, auto& scheduler)
                            { return std::make_shared<BranchStepSystem>(manager, scheduler); })
        .RegisterStepSystem([](auto& manager, auto& scheduler)
                            { return std::make_shared<SpokenLineStepSystem>(manager, scheduler); })
        .RegisterStepSystem([](auto& manager, auto&) { return std::make_shared<BeginDecisionTreeSystem>(manager); });

    AddUI<Vulkan::VulkanGraphicsBackend, NovelRT::Input::Glfw::GlfwInputBackend,
          NovelRT::Windowing::Glfw::GlfwWindowingBackend>(builder)
        .WithGraphicsDevice(gfxDevice)
        .WithGraphicsMemoryAllocator(memoryAllocator)
        .WithWindowProvider(wndProvider)
        .WithInputProvider(inputProvider)
        .WithResourceLoader(resourceLoader)
        .WithDefaultUIProvider(false)
        .AddFont("default", "Raleway-Regular.ttf")
        .WithDefaultUISystem()
        .WithGraphicsBuilder(gfx);

    gfx.WithDefaultOrchestrator();

    builder.Configure([defaultSpriteRenderer](SystemScheduler& scheduler)
                      { unused(scheduler.RegisterSystem(defaultSpriteRenderer)); });

    builder.Configure(
        [&wndProvider, &resourceLoader, &scriptManager](SystemScheduler& scheduler)
        {
            unused(scheduler.RegisterSystem(std::make_shared<ViewportUpdateSystem>(wndProvider)));
            unused(scheduler.RegisterSystem(std::make_shared<InitialisationSystem>(resourceLoader, scriptManager)));
            unused(scheduler.RegisterSystem(std::make_shared<PoseToSpriteTranslationSystem>(resourceLoader)));
            unused(scheduler.RegisterSystem(std::make_shared<BranchTranslationSystem>()));
            unused(scheduler.RegisterSystem(std::make_shared<SpokenLineTranslationSystem>()));
        });

    SystemScheduler scheduler = builder.Build();
    StepTimer timer{};
    Event<Timestamp::duration> TimerCallback{};

    TimerCallback += [&timer, &scheduler](auto /* delta */) { scheduler.ExecuteIteration(timer.getTotalTime()); };

    while (!wndProvider->ShouldClose())
    {
        wndProvider->ProcessAllMessages();
        timer.Tick(TimerCallback);
    }

    gfxDevice->WaitForIdle();

    return 0;
}
