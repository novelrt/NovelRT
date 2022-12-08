// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository
// root for more information.

#include <NovelRT/NovelRT.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Input;
using namespace NovelRT::PluginManagement;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

    DefaultPluginSelector selector;
    auto resourceManager = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>();
    auto windowingProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();
    auto inputProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>();
    auto graphicsProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>();
    auto scheduler =
        Configurator()
            .WithDefaultSystemsAndComponents()
            .WithPluginProvider(graphicsProvider)
            .WithPluginProvider(windowingProvider)
            .WithPluginProvider(inputProvider)
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>())
            .InitialiseAndRegisterComponents();

    std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Graphics::DefaultRenderingSystem>();

    NovelRT::Threading::FutureResult<NovelRT::Ecs::Graphics::TextureInfo> textureFuture =
        renderingSystem->GetOrLoadTexture("novel-chan");

    renderingSystem->ForceVertexTextureFutureResolution();

    auto transformBuffer = scheduler.GetComponentCache().GetComponentBuffer<TransformComponent>();
    auto entityGraphBuffer = scheduler.GetComponentCache().GetComponentBuffer<EntityGraphComponent>();

    EntityId parentEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childOfChildEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    transformBuffer.PushComponentUpdateInstruction(
        0, childEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::Zero(), 0});
    transformBuffer.PushComponentUpdateInstruction(
        0, childOfChildEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::Zero(), 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childEntity, EntityGraphComponent{true, parentEntity, 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childOfChildEntity, EntityGraphComponent{true, childEntity, 0});

    scheduler.RegisterSystem([](auto delta, auto catalogue) {
        ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();

        for (auto [entity, transform] : transforms)
        {
            TransformComponent newComponent{};
            newComponent.rotationInRadians = NovelRT::Maths::Utilities::DegreesToRadians(20 * delta.getSecondsFloat());
            newComponent.scale = NovelRT::Maths::GeoVector2F::Zero();
            transforms.PushComponentUpdateInstruction(entity, newComponent);
        }
    });

    scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    NovelRT::Timing::StepTimer timer;

    auto windowPtr = windowingProvider->GetWindowingDevice();
    windowPtr->SetWindowTitle("ECS Render Pipeline Test");

    std::shared_ptr<NovelRT::Ecs::Input::InputSystem> inputSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Input::InputSystem>();

    auto context = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsContext*>(renderingSystem->GetGraphicsDevice()->GetCurrentContext().get());
    auto device = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsDevice*>(context->GetDevice().get());
    auto graphicsQueue = device->GetVulkanGraphicsQueue();
    auto adapter = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsAdapter*>(device->GetAdapter().get());
    auto vkGraphicsProvider = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsProvider*>(graphicsProvider->GetGraphicsProvider().get());
    auto vkGraphicsPipeline = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsPipeline*>(renderingSystem->GetExistingPipelineInfo(parentEntity)->gpuPipeline.get());
    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    //ImGui Init
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font1 = io.Fonts->AddFontDefault();
    auto fontpath = resourceManager->GetResourceLoader()->ResourcesRootDirectory() / "Fonts" / "Raleway-Regular.ttf";
    auto fontpath2 = resourceManager->GetResourceLoader()->ResourcesRootDirectory() / "Fonts" / "Gayathri-Regular.ttf";
    const char* fontpath_cstr = fontpath.string().c_str();
    const char* fontpath_cstr2 = fontpath2.string().c_str();
    ImFont* font2 = io.Fonts->AddFontFromFileTTF(fontpath_cstr, 20.0f);
    ImFont* font3 = io.Fonts->AddFontFromFileTTF(fontpath_cstr2, 30.0f);


    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForVulkan(reinterpret_cast<GLFWwindow*>(windowPtr->GetHandle()),true);



    //ImGui Vulkan Init
    ImGui_ImplVulkan_InitInfo initInfo = {};
    initInfo.Instance = vkGraphicsProvider->GetVulkanInstance();
    initInfo.PhysicalDevice = adapter->GetVulkanPhysicalDevice();
    initInfo.Device = device->GetVulkanDevice();
    initInfo.QueueFamily = static_cast<uint32_t>(-1);
    initInfo.Queue = graphicsQueue;
    initInfo.PipelineCache = nullptr;
    initInfo.DescriptorPool = vkGraphicsPipeline->GetSignature()->GetVulkanDescriptorPool();
    initInfo.Subpass = 0;
    initInfo.MinImageCount = 2;
    initInfo.ImageCount = device->GetVulkanSwapChainImages().size();
    initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    initInfo.Allocator = nullptr;
    initInfo.CheckVkResultFn = [](VkResult err){
        if (err == 0) return;
        spdlog::error("Vulkan Error: VkResult = {}", err);
        if (err < 0)
        {
            abort();
        }
    };
    ImGui_ImplVulkan_Init(&initInfo, device->GetVulkanRenderPass());

    //ImGui Upload Fonts to GPU
    //might need to call begin here for cb
    //auto imGuiCommandBuffer = context->CreateVulkanCommandBuffer();
    VkCommandBufferBeginInfo commandBufferBeginInfo{};
    commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    vkBeginCommandBuffer(context->GetVulkanCommandBuffer(), &commandBufferBeginInfo);
    ImGui_ImplVulkan_CreateFontsTexture(context->GetVulkanCommandBuffer());
    vkEndCommandBuffer(context->GetVulkanCommandBuffer());

    auto vkBuffer = context->GetVulkanCommandBuffer();
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &vkBuffer;
    auto executeGraphicsFence = context->GetWaitForExecuteCompletionFence();

    VkResult queueSubmitResult = vkQueueSubmit(graphicsQueue, 1, &submitInfo,
                                                   executeGraphicsFence->GetVulkanFence());

    if (queueSubmitResult != VK_SUCCESS)
    {
        throw std::runtime_error("vkQueueSubmit failed! Reason: " + std::to_string(queueSubmitResult));
    }

    executeGraphicsFence->Wait();
    executeGraphicsFence->Reset();

    renderingSystem->UIRenderEvent += [&](auto system, NovelRT::Ecs::Graphics::DefaultRenderingSystem::UIRenderEventArgs args) {
        //Begin Frame
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();
        ImGui::Text("Hi im crappy default font text");
        ImGui::Text("");
        ImGui::PushFont(font2);
        ImGui::Text("HAHA_LMAO IM RALEWAY FROM THE FONTS FOLDER");
        ImGui::Text("");
        ImGui::PopFont();
        ImGui::PushFont(font3);
        ImGui::Text("KEKW IM Gayathri-Regular FROM THE FONTS FOLDER");
        ImGui::Text("");
        ImGui::PopFont();
        ImGui::Text("NOT brought to you by Freetype because im too tired to build that shit rn");


        //End Frame
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Render();

        //Render
        auto ctx = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsContext*>(args.graphicsContext.get());
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), ctx->GetVulkanCommandBuffer());

    };


    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
    }

    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
