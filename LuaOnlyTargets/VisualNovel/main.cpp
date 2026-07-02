// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>
#include <NovelRT/Ecs/Graphics/Components/Sprite.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Exceptions/FileNotFoundException.hpp>
#include <NovelRT/Maths/GeoVector2F.hpp>
#include <nlohmann/json_fwd.hpp>

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

#include <format>
#include <iterator>
#include <memory>
#include <nlohmann/json.hpp>

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

class SceneManagementSystem : public IEcsSystem
{
private:
    struct SceneData
    {
        uuids::uuid scriptPath;
        uuids::uuid backgroundImage;
    };

    std::shared_ptr<ResourceLoader> _resourceLoader;
    std::vector<SceneData> _sceneData;
    std::optional<EntityId> _backgroundSprite;
    size_t _index;
    std::shared_ptr<WindowProvider<NovelRT::Windowing::Glfw::GlfwWindowingBackend>> _wndProvider;

public:
    SceneManagementSystem(
        const std::shared_ptr<ResourceLoader>& resourceLoader,
        const std::shared_ptr<WindowProvider<NovelRT::Windowing::Glfw::GlfwWindowingBackend>>& wndProvider)
        : _resourceLoader(resourceLoader), _index(0ULL), _wndProvider(wndProvider)
    {
        auto vnConfig = _resourceLoader->LoadPlaintextAsset("VNConfig.json");
        auto jsonData = nlohmann::json::parse(vnConfig.bytes);
        auto jsonAsVector = jsonData.get<std::vector<nlohmann::json>>();

        std::transform(
            jsonAsVector.begin(), jsonAsVector.end(), std::back_inserter(_sceneData),
            [&](const nlohmann::json& jsonEntry)
            {
                auto scriptPath =
                    _resourceLoader->TryGetAssetIdBasedOnFilePath(jsonEntry["scriptPath"].get<std::string>());

                auto backgroundImagePath =
                    _resourceLoader->TryGetAssetIdBasedOnFilePath(jsonEntry["backgroundImagePath"].get<std::string>());

                if (!scriptPath.has_value() || !backgroundImagePath.has_value())
                {
                    throw NovelRT::Exceptions::FileNotFoundException(
                        std::format("Failed to find either {0} or {1}", jsonEntry["scriptPath"].get<std::string>(),
                                    jsonEntry["scriptPath"].get<std::string>()));
                }

                return SceneData{.scriptPath = scriptPath.value(), .backgroundImage = backgroundImagePath.value()};
            });
    }

    void Update(NovelRT::Timing::Timestamp /*delta*/, Catalogue catalogue) final
    {
        auto [spritesView, transformsView, decisionTreeLoadRequestView, activeDecisionTreesView,
              loadedDecisionTreesView] =
            catalogue.GetComponentViews<NovelRT::Ecs::Graphics::Components::Sprite,
                                        NovelRT::Ecs::Components::TransformComponent,
                                        NovelRT::Ecs::Scripting::Components::DecisionTreeLoadRequest,
                                        NovelRT::Ecs::Scripting::Components::ActiveDecisionTree,
                                        NovelRT::Ecs::Scripting::Components::LoadedDecisionTree>();

        if (!_backgroundSprite.has_value())
        {
            auto entity = catalogue.CreateEntity();

            transformsView.AddComponent(entity);

            spritesView.AddComponent(
                entity, NovelRT::Ecs::Graphics::Components::Sprite{.assetId = _sceneData.at(0).backgroundImage});

            decisionTreeLoadRequestView.AddComponent(
                entity,
                NovelRT::Ecs::Scripting::Components::DecisionTreeLoadRequest{.assetId = _sceneData.at(0).scriptPath});

            _backgroundSprite = entity;
        }

        if (decisionTreeLoadRequestView.HasComponent(_backgroundSprite.value()) ||
            activeDecisionTreesView.HasComponent(_backgroundSprite.value()))
        {
            return;
        }

        if (loadedDecisionTreesView.HasComponent(_backgroundSprite.value()))
        {
            _index++;

            if (_index >= _sceneData.size())
            {
                _wndProvider->Close();
                return;
            }

            spritesView.PushComponentUpdateInstruction(
                _backgroundSprite.value(),
                NovelRT::Ecs::Graphics::Components::Sprite{.assetId = _sceneData.at(_index).backgroundImage});

            decisionTreeLoadRequestView.PushComponentUpdateInstruction(
                _backgroundSprite.value(), NovelRT::Ecs::Scripting::Components::DecisionTreeLoadRequest{
                                               .assetId = _sceneData.at(_index).scriptPath});
        }
    }
};

class InitialisationSystem : public IEcsSystem
{
private:
    bool _initialized = false;
    NovelRT::Maths::GeoVector2F _dimensions;

public:
    explicit InitialisationSystem(NovelRT::Maths::GeoVector2F initialDimensions) noexcept
        : _dimensions(initialDimensions)
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

        auto worldCameraEntity = catalogue.CreateEntity();
        auto screenCameraEntity = catalogue.CreateEntity();

        transforms.PushComponentUpdateInstruction(
            worldCameraEntity, NovelRT::Ecs::Components::TransformComponent{.position = GeoVector2F{0.0f, 0.0f},
                                                                            .scale = GeoVector2F{1.0f, 1.0f},
                                                                            .rotationInRadians = 0.0f});

        cameras.PushComponentUpdateInstruction(
            worldCameraEntity, NovelRT::Ecs::Graphics::Components::Camera{.left = -1.0f,
                                                                          .right = 1.0f,
                                                                          .bottom = 1.0f,
                                                                          .top = -1.0f,
                                                                          .nearPlane = 0.0f,
                                                                          .farPlane = 1.0f,
                                                                          .referenceResolutionWidth = 1920,
                                                                          .referenceResolutionHeight = 1080});
        cameras.PushComponentUpdateInstruction(
            screenCameraEntity, NovelRT::Ecs::Graphics::Components::Camera{.left = -1.0f,
                                                                           .right = 1.0f,
                                                                           .bottom = 1.0f,
                                                                           .top = -1.0f,
                                                                           .nearPlane = 0.0f,
                                                                           .farPlane = 1.0f,
                                                                           .referenceResolutionWidth = 1920,
                                                                           .referenceResolutionHeight = 1080,
                                                                           .isScreenSpace = true});

        viewports.PushComponentUpdateInstruction(
            worldCameraEntity, NovelRT::Ecs::Graphics::Components::Viewport{.width = _dimensions.x, .height = _dimensions.y});
        viewports.PushComponentUpdateInstruction(
            screenCameraEntity, NovelRT::Ecs::Graphics::Components::Viewport{.width = _dimensions.x, .height = _dimensions.y});
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
        auto [loadedTrees, activeTrees, loadRequests] =
            catalogue.GetComponentViews<NovelRT::Ecs::Scripting::Components::LoadedDecisionTree,
                                        NovelRT::Ecs::Scripting::Components::ActiveDecisionTree,
                                        NovelRT::Ecs::Scripting::Components::DecisionTreeLoadRequest>();

        for (const auto& [entity, tree] : loadedTrees)
        {
            if (activeTrees.HasComponent(entity))
            {
                continue;
            }

            unused(loadRequests.TryRemoveComponent(entity));

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
            // it doesn't actually matter what the viewport sizes are if we are minimising.
            // This is a Windows 11 specific fix. - Matt J.
            if (eventArgs == NovelRT::Maths::GeoVector2F::Zero())
            {
                return;
            }

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

    auto wndProvider = std::make_shared<WindowProvider<NovelRT::Windowing::Glfw::GlfwWindowingBackend>>();

    auto finalSize = wndProvider->GetAllVideoModeData().at(0).displayDimensions * 0.75f;

    wndProvider->CreateWindow(NovelRT::Windowing::WindowMode::Windowed, finalSize);

    auto inputProvider = std::make_shared<InputProvider<NovelRT::Input::Glfw::GlfwInputBackend>>(wndProvider);

    auto scriptManager = std::make_shared<ScriptManager>();
    auto resourceLoader = std::make_shared<DesktopResourceLoader>();

    auto gfxProvider = wndProvider->CreateGraphicsProvider<VulkanGraphicsBackend>(false);
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider, gfxSurfaceContext);
    auto gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext);
    auto memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(gfxDevice, gfxProvider);

    resourceLoader->InitAssetDatabase();

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

    auto defaultSpriteRenderer = std::make_shared<SpriteRendererSystem<VulkanGraphicsBackend>>(
        gfxDevice, passData, resourceLoader, memoryAllocator, gfxSurfaceContext);

    builder.Configure([defaultSpriteRenderer](SystemScheduler& scheduler)
                      { unused(scheduler.RegisterSystem(defaultSpriteRenderer)); });

    builder.Configure(
        [&wndProvider, &resourceLoader, finalSize = finalSize](SystemScheduler& scheduler)
        {
            unused(scheduler.RegisterSystem(std::make_shared<ViewportUpdateSystem>(wndProvider)));
            unused(scheduler.RegisterSystem(std::make_shared<InitialisationSystem>(finalSize)));
            unused(scheduler.RegisterSystem(std::make_shared<PoseToSpriteTranslationSystem>(resourceLoader)));
            unused(scheduler.RegisterSystem(std::make_shared<BranchTranslationSystem>()));
            unused(scheduler.RegisterSystem(std::make_shared<SpokenLineTranslationSystem>()));
            unused(scheduler.RegisterSystemDependsOnAll(
                std::make_shared<SceneManagementSystem>(resourceLoader, wndProvider)));
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
