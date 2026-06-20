// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/Camera.hpp>
#include <NovelRT/Ecs/Graphics/Components/Viewport.hpp>
#include <NovelRT/Ecs/Graphics/EcsGraphicsBuilder.hpp>
#include <NovelRT/Ecs/Graphics/RenderOrchestratorSystem.hpp>
#include <NovelRT/Ecs/Graphics/RenderPassManager.hpp>
#include <NovelRT/Ecs/Graphics/SpriteRendererSystem.hpp>

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

#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>

#include <NovelRT/Ecs/UI/Components/UIButton.hpp>
#include <NovelRT/Ecs/UI/Components/UIClickEvent.hpp>
#include <NovelRT/Ecs/UI/Components/UIElement.hpp>
#include <NovelRT/Ecs/UI/Components/UIText.hpp>
#include <NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp>
#include <NovelRT/Ecs/UI/EcsUIBuilder.hpp>
#include <NovelRT/Ecs/UI/UIComponentType.hpp>
#include <NovelRT/Ecs/UI/UISystem.hpp>

#include <NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>

#include <NovelRT/Timing/StepTimer.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <memory>
#include <optional>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Components;
using namespace NovelRT::Ecs::Graphics;
using namespace NovelRT::Ecs::Graphics::Components;
using namespace NovelRT::Logging;
using namespace NovelRT::Graphics;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Timing;
using namespace NovelRT::Windowing;
using namespace NovelRT::Utilities;
using namespace NovelRT::ResourceManagement::Desktop;
using namespace NovelRT::Timing;
using namespace NovelRT::Maths;
using namespace NovelRT::UI::ImGui;
using namespace NovelRT::Ecs::UI;
using namespace NovelRT::Ecs::UI::Components;
using namespace NovelRT::Input;

class SpriteSetupSystem : public IEcsSystem
{
private:
    std::optional<EntityId> _spriteEntity;
    std::optional<EntityId> _cameraViewportEntity;
    std::shared_ptr<DesktopResourceLoader> _resourceLoader;
    NovelRT::Maths::GeoVector2F _viewportSize;

public:
    explicit SpriteSetupSystem(std::shared_ptr<DesktopResourceLoader> resourceLoader, GeoVector2F viewportSize)
        : _resourceLoader(std::move(resourceLoader)), _viewportSize(viewportSize)
    {
    }

    void Update(NovelRT::Timing::Timestamp /*delta*/, Catalogue catalogue) final
    {
        if (_spriteEntity.has_value() && _cameraViewportEntity.has_value())
        {
            return;
        }

        auto [spriteView, transformView, graphView, cameraView, viewportView] = catalogue.GetComponentViews<
            NovelRT::Ecs::Graphics::Components::Sprite, NovelRT::Ecs::Components::TransformComponent,
            NovelRT::Ecs::Components::EntityGraphComponent, NovelRT::Ecs::Graphics::Components::Camera,
            NovelRT::Ecs::Graphics::Components::Viewport>();

        auto spriteEntity = catalogue.CreateEntity();
        _spriteEntity = spriteEntity;

        auto assetId = _resourceLoader->TryGetAssetIdBasedOnFilePath("Images/milk-carton-hi.png").value();

        NovelRT::Ecs::Graphics::Components::Sprite sprite{};
        sprite.assetId = assetId;
        spriteView.AddComponent(spriteEntity, sprite);

        NovelRT::Ecs::Components::TransformComponent transform{};
        transform.position = NovelRT::Maths::GeoVector2F(0.0f, 0.0f);
        transform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
        transform.rotationInRadians = 0.0f;
        transformView.AddComponent(spriteEntity, transform);

        EntityGraphComponent graphComp{};
        graphComp.parent = std::numeric_limits<EntityId>::max();
        graphComp.childrenStartNode = std::numeric_limits<EntityId>::max();
        graphView.AddComponent(spriteEntity, graphComp);

        auto cameraViewportEntity = catalogue.CreateEntity();
        _cameraViewportEntity = cameraViewportEntity;

        NovelRT::Ecs::Components::TransformComponent viewportTransform{};
        viewportTransform.position = NovelRT::Maths::GeoVector2F(0.0f, 0.0f);
        viewportTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
        viewportTransform.rotationInRadians = 0.0f;
        transformView.AddComponent(cameraViewportEntity, viewportTransform);

        auto size = _viewportSize;

        NovelRT::Ecs::Graphics::Components::Camera camera{};
        camera.left = -1.0f;
        camera.right = 1.0f;
        camera.top = -1.0f;
        camera.bottom = 1.0f;
        camera.nearPlane = 0.0f;
        camera.farPlane = 1.0f;
        camera.referenceResolutionWidth = 1920;
        camera.referenceResolutionHeight = 1080;

        cameraView.AddComponent(cameraViewportEntity, camera);

        NovelRT::Ecs::Graphics::Components::Viewport viewport{};
        viewport.width = size.x;
        viewport.height = size.y;

        viewportView.AddComponent(cameraViewportEntity, viewport);
    }
};

class UISetupSystem : public IEcsSystem
{
private:
    bool _firstPass = true;
    int32_t _initialWidth;
    int32_t _initialHeight;

public:
    UISetupSystem(NovelRT::Maths::GeoVector2F& initialSize):
        _initialWidth(initialSize.x),
        _initialHeight(initialSize.y)
    {
    }

    void Update(NovelRT::Timing::Timestamp /*delta*/, Catalogue catalogue) final
    {
        if (!_firstPass)
        {
            return;
        }
        _firstPass = false;

        auto [elementView, containerView, buttonView, textView, transformView, graphView, camView] =
            catalogue.GetComponentViews<UIElement, UIWidgetContainer, UIButton, UIText, TransformComponent,
                                        EntityGraphComponent, Camera>();

        // setup the screen space camera
        auto cameraId = catalogue.CreateEntity();
        NovelRT::Ecs::Graphics::Components::Camera camera{};
        camera.isScreenSpace = true;
        camera.referenceResolutionWidth = _initialWidth;
        camera.referenceResolutionHeight = _initialHeight;
        camView.AddComponent(cameraId, camera);

        // container - this is the "box" for the textbox
        auto rootId = catalogue.CreateEntity();

        elementView.AddComponent(rootId, UIElement{rootId, UIComponentType::Container});
        containerView.AddComponent(rootId, UIWidgetContainer{"NarrativeTextbox", false});
        transformView.AddComponent(rootId,
                                   TransformComponent{GeoVector2F(100.0f, 500.0f), GeoVector2F(612.0f, 200.0f), 0.0f});
        graphView.AddComponent(rootId, EntityGraphComponent{});

        EntityGraphView rootView{catalogue, rootId, EntityGraphComponent{}};

        // Now the text
        auto textId = catalogue.CreateEntity();

        elementView.AddComponent(textId, UIElement{textId, UIComponentType::Text});
        textView.AddComponent(textId, UIText{"", RGBAColour(255, 255, 255, 255)});
        graphView.AddComponent(textId, EntityGraphComponent{true, rootId});
        rootView.AddInsertChildInstruction(textId);

        // Now the button - ordering is important!
        auto buttonId = catalogue.CreateEntity();
        uint64_t clickEventId =
            1; // any number for this example will do, but you should be very explicit on event Ids in real systems
        elementView.AddComponent(buttonId, UIElement{buttonId, UIComponentType::Button});
        buttonView.AddComponent(buttonId,
                                UIButton{
                                    "Next",
                                    clickEventId,
                                    NovelRT::Graphics::RGBAColour{0, 102, 204, 255}, // bg
                                    NovelRT::Graphics::RGBAColour{0, 82, 163, 255},                        // active
                                    NovelRT::Graphics::RGBAColour{0, 119, 255, 255},                       // hovered
                                    NovelRT::Graphics::RGBAColour{255, 255, 255, 255},                     // text
                                });
        transformView.AddComponent(buttonId,
                                   TransformComponent{GeoVector2F(500.0f, 150.0f), GeoVector2F(80.0f, 30.0f), 0.0f});
        graphView.AddComponent(buttonId, EntityGraphComponent{true, rootId});
        rootView.AddInsertChildInstruction(buttonId);
    }
};

class UIInteractionSystem : public IEcsSystem
{
private:
    std::optional<EntityId> _button;
    std::optional<EntityId> _text;
    uint32_t _strIndex = 0;

    std::vector<std::string> _story{"Hello!", "I'm going to get milk, now...", "...", "...", "*30 years later*", "..."};

public:
    void Update(NovelRT::Timing::Timestamp /*delta*/, Catalogue catalogue) final
    {
        auto [elementView, clickEvents, textView, buttonView, spriteView] =
            catalogue.GetComponentViews<UIElement, UIClickEvent, UIText, UIButton, Sprite>();

        // You may want to cache these entities for now, but I'm not
        // so we're going to search for them since there's a singular button and text object.
        if (!_button.has_value() || !_text.has_value())
        {
            for (auto [id, element] : elementView)
            {
                if (!_button.has_value() && element.Type == UIComponentType::Button)
                {
                    _button = id;
                }
                if (!_text.has_value() && element.Type == UIComponentType::Text)
                {
                    _text = id;
                    UIText initialText{};
                    if (textView.TryGetComponent(id, initialText))
                    {
                        textView.PushComponentUpdateInstruction(
                            id, UIText{_story[_strIndex].c_str(), initialText.colour});
                    }
                }
            }
        }

        if (_button.has_value())
        {
            // Click events can have event "id"s but there's only one here.
            UIClickEvent click{};
            if (clickEvents.TryGetComponent(_button.value(), click))
            {
                _strIndex++;

                if (_text.has_value())
                {
                    UIText text{};
                    if (textView.TryGetComponent(_text.value(), text))
                    {
                        if (_strIndex < _story.size())
                        {
                            text.textValue = _story[_strIndex].c_str();
                        }
                        else
                        {
                            text.textValue = "...";

                            // slightly fade the milk away...
                            for (auto [spriteId, component] : spriteView)
                            {
                                RGBAColour tinted = component.tint;
                                if (tinted.a > 5)
                                {
                                    tinted.a -= 25;
                                    spriteView.PushComponentUpdateInstruction(spriteId,
                                                                              Sprite{component.assetId, tinted});
                                }
                                else
                                {
                                    tinted.a = 0;
                                    spriteView.PushComponentUpdateInstruction(spriteId,
                                                                              Sprite{component.assetId, tinted});
                                }
                            }
                        }
                        textView.PushComponentUpdateInstruction(_text.value(), text);
                    }
                }

                // remove the event
                clickEvents.RemoveComponent(_button.value());
            }
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
        if(!_changedSize)
        {
            return;
        }

        _changedSize = false;

        auto [viewports] = catalogue.GetComponentViews<Viewport>();

        for(auto [entity, viewport] : viewports)
        {
            unused(viewport);
            NovelRT::Ecs::Graphics::Components::Viewport newViewport{};
            newViewport.width = _size.x;
            newViewport.height = _size.y;
            viewports.PushComponentUpdateInstruction(entity, newViewport);
        }
    }
};

int main()
{
    // Setup your providers, etc.
    auto resourceLoader = std::make_shared<DesktopResourceLoader>();
    resourceLoader
        ->InitAssetDatabase(); // TODO: Hack because this was originally called by the legacy plugin provider stuff.

    auto windowSize = NovelRT::Maths::GeoVector2F(800, 800);
    auto wndProvider = std::make_shared<WindowProvider<NovelRT::Windowing::Glfw::GlfwWindowingBackend>>(
        NovelRT::Windowing::WindowMode::Windowed, windowSize);

    auto inputProvider = std::make_shared<InputProvider<NovelRT::Input::Glfw::GlfwInputBackend>>(wndProvider);

    auto gfxProvider = wndProvider->CreateGraphicsProvider<VulkanGraphicsBackend>(true);
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider, gfxSurfaceContext);
    auto gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext);
    auto memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(gfxDevice, gfxProvider);

    SystemSchedulerBuilder builder{};
    SpriteRendererSystem<VulkanGraphicsBackend>::SpritePass passData{};
    std::shared_ptr<ViewportUpdateSystem> viewportUpdater = std::make_shared<ViewportUpdateSystem>(wndProvider);

    // Build your default systems
    AddDefaults(builder);
    auto& gfxBuilder = AddGraphics<Vulkan::VulkanGraphicsBackend>(builder)
                           .WithGraphicsDevice(gfxDevice)
                           .WithSurfaceContext(gfxSurfaceContext)
                           .ConfigureRenderPasses(
                               [gfxDevice, &passData](RenderPassManager<VulkanGraphicsBackend>& renderPassManager)
                               {
                                   GraphicsRenderPassDescription passDesc{};
                                   GraphicsAttachmentDescription attachmentDesc{};

                                   attachmentDesc.texelFormat = gfxDevice->GetSwapchain()->GetFormat();
                                   attachmentDesc.loadOp = LoadOp::Clear;
                                   attachmentDesc.storeOp = StoreOp::Store;
                                   attachmentDesc.initialLayout = ImageLayout::Present;
                                   attachmentDesc.finalLayout = ImageLayout::Present;

                                   passDesc.attachmentDescriptions.push_back(attachmentDesc);
                                   passData.RenderPass = gfxDevice->CreateRenderPass(passDesc);
                                   passData.RenderPassId = renderPassManager.RegisterRenderPass(passData.RenderPass);
                               })
                           .WithDefaultBackgroundColour(0, 0, 0, 255);

    AddUI<Vulkan::VulkanGraphicsBackend, NovelRT::Input::Glfw::GlfwInputBackend,
          NovelRT::Windowing::Glfw::GlfwWindowingBackend>(builder)
        .WithGraphicsDevice(gfxDevice)
        .WithGraphicsMemoryAllocator(memoryAllocator)
        .WithWindowProvider(wndProvider)
        .WithInputProvider(inputProvider)
        .WithDefaultUIProvider(false)
        .AddFont("default", "Raleway-Regular.ttf")
        .WithDefaultUISystem()
        .WithGraphicsBuilder(gfxBuilder);

    gfxBuilder.WithDefaultOrchestrator();

    auto defaultSpriteRenderer = std::make_shared<SpriteRendererSystem<VulkanGraphicsBackend>>(
        gfxDevice, passData, resourceLoader, memoryAllocator, gfxSurfaceContext);

    // Add your systems and configure them
    auto setupSystem = std::make_shared<SpriteSetupSystem>(resourceLoader, GeoVector2F(1920.0f, 1080.0f) / 2.0f);
    auto uiSetupSystem = std::make_shared<UISetupSystem>(windowSize);
    auto clickSystem = std::make_shared<UIInteractionSystem>();

    builder.Configure([defaultSpriteRenderer](SystemScheduler& scheduler)
                      { unused(scheduler.RegisterSystem(defaultSpriteRenderer)); });
    builder.Configure([setupSystem](SystemScheduler& scheduler) { unused(scheduler.RegisterSystem(setupSystem)); });
    builder.Configure([uiSetupSystem](SystemScheduler& scheduler) { unused(scheduler.RegisterSystem(uiSetupSystem)); });
    builder.Configure([clickSystem](SystemScheduler& scheduler) { unused(scheduler.RegisterSystem(clickSystem)); });
    builder.Configure([viewportUpdater](SystemScheduler& scheduler) { unused(scheduler.RegisterSystem(viewportUpdater)); });

    SystemScheduler scheduler = builder.Build();
    StepTimer timer{};
    Event<Timestamp::duration> TimerCallback{};

    TimerCallback += [&scheduler](auto delta) { scheduler.ExecuteIteration(Timestamp{delta}); };

    while (!wndProvider->ShouldClose())
    {
        wndProvider->ProcessAllMessages();
        timer.Tick(TimerCallback);
    }

    gfxDevice->WaitForIdle();

    return 0;
}
