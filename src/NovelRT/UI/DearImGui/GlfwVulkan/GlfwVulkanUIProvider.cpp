// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/DearImGui/GlfwVulkan/UI.DearImGui.GlfwVulkan.h>

namespace NovelRT::UI::DearImGui::GlfwVulkan
{
    GlfwVulkanUIProvider::GlfwVulkanUIProvider() noexcept
        : UIProvider(),
          _isInitialised(false),
          _initInfo(),
          _windowSize(),
          _fontNameMapping(std::map<std::string, ImFont*>()),
          _currentCommandListFinished(false),
          _buttonCache(std::map<const char*, bool>()),
          _factory()
    {
    }

    void GlfwVulkanUIProvider::Initialise(std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> resourceLoader,
                                          std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
                                          std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
                                          std::shared_ptr<NovelRT::Input::IInputDevice> inputDevice,
                                          std::shared_ptr<NovelRT::Graphics::GraphicsProvider> gfxProvider,
                                          std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline)
    {
        _logger.logDebugLine("Initialising Dear ImGui UI service with GLFW and Vulkan...");
        if (resourceLoader == nullptr)
        {
            _logger.logErrorLine(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as ResourceLoader!");
            throw NovelRT::Exceptions::NullPointerException(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as ResourceLoader!");
        }
        if (gfxDevice == nullptr)
        {
            _logger.logErrorLine(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as GraphicsDevice!");
            throw NovelRT::Exceptions::NullPointerException(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as GraphicsDevice!");
        }
        if (windowingDevice == nullptr)
        {
            _logger.logErrorLine(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as IWindowingDevice!");
            throw NovelRT::Exceptions::NullPointerException(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as IWindowingDevice!");
        }
        if (inputDevice == nullptr)
        {
            _logger.logErrorLine(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as IInputDevice!");
            throw NovelRT::Exceptions::NullPointerException(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as IInputDevice!");
        }
        if (gfxDevice == nullptr)
        {
            _logger.logErrorLine("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as "
                                 "IGraphicsPluginProvider!");
            throw NovelRT::Exceptions::NullPointerException("Could not initialise Dear ImGui with GLFW and Vulkan - "
                                                            "null pointer provided as IGraphicsPluginProvider!");
        }
        if (pipeline == nullptr)
        {
            _logger.logErrorLine(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as GraphicsPipeline!");
            throw NovelRT::Exceptions::NullPointerException(
                "Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as GraphicsPipeline!");
        }
        _resourceLoader = resourceLoader;
        auto vulkanProvider = std::dynamic_pointer_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsProvider>(gfxProvider);
        auto vulkanDevice = std::dynamic_pointer_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsDevice>(gfxDevice);
        auto vulkanPipeline = std::dynamic_pointer_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsPipeline>(pipeline);
        _windowSize = windowingDevice->GetSize();
        windowingDevice->SizeChanged += [&](NovelRT::Maths::GeoVector2F args) { _windowSize = args; };
        // Init Dear ImGui Context
        ImGui::CreateContext();

        auto fontsPath = _resourceLoader->ResourcesRootDirectory() / "Fonts";
        for (auto const& entry : std::filesystem::directory_iterator{fontsPath})
        {
            if (entry.is_regular_file())
            {
                if (entry.path().extension() == ".ttf")
                {
                    auto metadata = _resourceLoader->LoadFont(entry.path());
                    _fontNameMapping.emplace(metadata.name, reinterpret_cast<ImFont*>(metadata.fontData));
                    _logger.logDebug("Dear ImGui - Loaded font: {}", metadata.name);
                }
            }
        }

        // GLFW Specific Init
        ImGui_ImplGlfw_InitForVulkan(reinterpret_cast<GLFWwindow*>(windowingDevice->GetHandle()), true);

        // Mimicking installation of callbacks a la what Dear ImGui does for its provided backends
        inputDevice->KeyPressHandler += [&](auto device, NovelRT::Input::NovelKey key, NovelRT::Input::KeyState state)
        {
            ImGuiIO& io = ImGui::GetIO();
            io.AddKeyEvent(GlfwToImGuiKey(key.GetExternalKeyCode()), (state == NovelRT::Input::KeyState::KeyDown ||
                                                                      state == NovelRT::Input::KeyState::KeyDownHeld));
            unused(device);
        };

        inputDevice->MouseButtonHandler += [](auto device, NovelRT::Input::NovelKey key, NovelRT::Input::KeyState state)
        {
            ImGuiIO& io = ImGui::GetIO();
            int32_t button = key.GetExternalKeyCode();
            if (button >= 0 && button < ImGuiMouseButton_COUNT)
                io.AddMouseButtonEvent(button, (state == NovelRT::Input::KeyState::KeyDown ||
                                                state == NovelRT::Input::KeyState::KeyDownHeld));
            unused(device);
        };

        inputDevice->MousePositionHandler += [](auto device, float x, float y)
        {
            ImGuiIO& io = ImGui::GetIO();
            io.AddMousePosEvent(x, y);
            unused(device);
        };

        inputDevice->UpdateHandler += [&](auto device)
        {
            ImGuiIO& io = ImGui::GetIO();
            device->MousePositionInterrupt() = io.WantSetMousePos;
            device->MouseButtonInterrupt() = io.WantCaptureMouse;
            device->KeyPressInterrupt() = io.WantCaptureKeyboard;
        };

        // Vulkan Specific Init
        _initInfo.Instance = vulkanProvider->GetVulkanInstance();
        _initInfo.PhysicalDevice = vulkanDevice->GetAdapter()->GetVulkanPhysicalDevice();
        _initInfo.Device = vulkanDevice->GetVulkanDevice();
        _initInfo.QueueFamily = static_cast<uint32_t>(-1);
        _initInfo.Queue = vulkanDevice->GetVulkanGraphicsQueue();
        _initInfo.PipelineCache = nullptr;
        _initInfo.DescriptorPool = vulkanPipeline->GetSignature()->GetVulkanDescriptorPool();
        _initInfo.Subpass = 0;
        _initInfo.MinImageCount = 2;
        _initInfo.ImageCount = static_cast<uint32_t>(vulkanDevice->GetVulkanSwapChainImages().size());
        _initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        _initInfo.Allocator = nullptr;
        _initInfo.CheckVkResultFn = [](VkResult err)
        {
            if (err == 0)
                return;
            spdlog::error("Vulkan Error: VkResult = {}", err);
            if (err < 0)
            {
                std::runtime_error("Vulkan check failed! Reason: " + std::to_string(err));
            }
        };
        ImGui_ImplVulkan_Init(&_initInfo, vulkanDevice->GetVulkanRenderPass());

        // Fonts init
        _logger.logDebugLine("Dear ImGui - uploading default fonts...");
        VkCommandBufferBeginInfo commandBufferBeginInfo{};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        VkCommandBuffer buffer = vulkanDevice->GetCurrentContext()->CreateVulkanCommandBuffer();

        vkBeginCommandBuffer(buffer, &commandBufferBeginInfo);
        ImGui_ImplVulkan_CreateFontsTexture(buffer);
        vkEndCommandBuffer(buffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &buffer;
        auto executeGraphicsFence = vulkanDevice->GetCurrentContext()->GetWaitForExecuteCompletionFence();

        VkResult queueSubmitResult = vkQueueSubmit(vulkanDevice->GetVulkanGraphicsQueue(), 1, &submitInfo,
                                                   executeGraphicsFence->GetVulkanFence());

        if (queueSubmitResult != VK_SUCCESS)
        {
            throw std::runtime_error("vkQueueSubmit failed! Reason: " + std::to_string(queueSubmitResult));
        }

        executeGraphicsFence->Wait();
        executeGraphicsFence->Reset();

        _isInitialised = true;
        _logger.logDebugLine("Initialised Dear ImGui UI service with GLFW and Vulkan successfully.");
    }

    void GlfwVulkanUIProvider::Begin()
    {
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void GlfwVulkanUIProvider::Render()
    {
        if (_currentCommandListFinished && _currentCommandList.size() > 0)
        {
            for (auto& cmd : _currentCommandList)
            {
                cmd();
            }
            _previousCommandList.clear();
            _previousCommandList.swap(_currentCommandList);
        }
        else if (_previousCommandList.size() > 0)
        {
            for (auto& cmd : _previousCommandList)
            {
                cmd();
            }
        }
    }

    void GlfwVulkanUIProvider::Update()
    {
        if (_currentCommandListFinished)
        {
            _currentCommandListFinished = false;
            _currentCommandList.clear();
        }

        for (auto& [u, e] : _elements)
        {
            GenerateCommand(e);
        }
        _currentCommandListFinished = true;
    }

    void GlfwVulkanUIProvider::End(std::shared_ptr<NovelRT::Graphics::GraphicsContext> context)
    {
        auto ctx = std::dynamic_pointer_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsContext>(context);
        ImGuiIO& io = ImGui::GetIO();
        unused(io);
        ImGui::Render();
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), ctx->GetVulkanCommandBuffer());
    }

    GlfwVulkanUIProvider::~GlfwVulkanUIProvider()
    {
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void GlfwVulkanUIProvider::GenerateCommand(std::shared_ptr<UIElement> element)
    {
        //std::vector<std::function<void()>> que = std::vector<std::function<void()>>();
        auto windowSize = _windowSize;
        switch (element->Type)
        {
            case UIElementType::Panel:
            {
                if (element->State == UIElementState::Shown)
                {
                    auto panel = std::static_pointer_cast<UIPanel>(element);
                    // Define the push / begin functions
                    auto colourPush = std::function<void()>(
                        [panel]() {
                            ImGui::PushStyleColor(ImGuiCol_WindowBg, panel->Colour.Get32BitColour()); });
                    auto panelBegin = std::function<void()>(
                        [panel]()
                        {
                            auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
                                             ImGuiWindowFlags_NoResize;
                            ImGui::Begin(panel->Identifer, nullptr, flags);
                        });
                    auto panelScale = std::function<void()>([panel]() { ImGui::SetWindowSize(panel->Scale); });
                    auto panelSize = std::function<void()>([panel, windowSize]() {
                        auto translatedPosition = panel->Position + (windowSize / 2);
                        ImGui::SetWindowPos(translatedPosition);
                    });
                    auto panelEnd = std::function<void()>([]() { ImGui::End(); });
                    // For every push there's a pop.
                    auto colourPop = std::function<void()>([panel]() { ImGui::PopStyleColor(); });

                    _currentCommandList.emplace_back(colourPush);
                    _currentCommandList.emplace_back(panelBegin);
                    _currentCommandList.emplace_back(panelSize);
                    _currentCommandList.emplace_back(panelScale);
                    _currentCommandList.emplace_back(panelEnd);
                    _currentCommandList.emplace_back(colourPop);
                }

                break;
            }
            default:
                return;
        }
    }

    ImGuiKey GlfwVulkanUIProvider::GlfwToImGuiKey(int32_t key)
    {
        switch (key)
        {
            case GLFW_KEY_TAB:
                return ImGuiKey_Tab;
            case GLFW_KEY_LEFT:
                return ImGuiKey_LeftArrow;
            case GLFW_KEY_RIGHT:
                return ImGuiKey_RightArrow;
            case GLFW_KEY_UP:
                return ImGuiKey_UpArrow;
            case GLFW_KEY_DOWN:
                return ImGuiKey_DownArrow;
            case GLFW_KEY_PAGE_UP:
                return ImGuiKey_PageUp;
            case GLFW_KEY_PAGE_DOWN:
                return ImGuiKey_PageDown;
            case GLFW_KEY_HOME:
                return ImGuiKey_Home;
            case GLFW_KEY_END:
                return ImGuiKey_End;
            case GLFW_KEY_INSERT:
                return ImGuiKey_Insert;
            case GLFW_KEY_DELETE:
                return ImGuiKey_Delete;
            case GLFW_KEY_BACKSPACE:
                return ImGuiKey_Backspace;
            case GLFW_KEY_SPACE:
                return ImGuiKey_Space;
            case GLFW_KEY_ENTER:
                return ImGuiKey_Enter;
            case GLFW_KEY_ESCAPE:
                return ImGuiKey_Escape;
            case GLFW_KEY_APOSTROPHE:
                return ImGuiKey_Apostrophe;
            case GLFW_KEY_COMMA:
                return ImGuiKey_Comma;
            case GLFW_KEY_MINUS:
                return ImGuiKey_Minus;
            case GLFW_KEY_PERIOD:
                return ImGuiKey_Period;
            case GLFW_KEY_SLASH:
                return ImGuiKey_Slash;
            case GLFW_KEY_SEMICOLON:
                return ImGuiKey_Semicolon;
            case GLFW_KEY_EQUAL:
                return ImGuiKey_Equal;
            case GLFW_KEY_LEFT_BRACKET:
                return ImGuiKey_LeftBracket;
            case GLFW_KEY_BACKSLASH:
                return ImGuiKey_Backslash;
            case GLFW_KEY_RIGHT_BRACKET:
                return ImGuiKey_RightBracket;
            case GLFW_KEY_GRAVE_ACCENT:
                return ImGuiKey_GraveAccent;
            case GLFW_KEY_CAPS_LOCK:
                return ImGuiKey_CapsLock;
            case GLFW_KEY_SCROLL_LOCK:
                return ImGuiKey_ScrollLock;
            case GLFW_KEY_NUM_LOCK:
                return ImGuiKey_NumLock;
            case GLFW_KEY_PRINT_SCREEN:
                return ImGuiKey_PrintScreen;
            case GLFW_KEY_PAUSE:
                return ImGuiKey_Pause;
            case GLFW_KEY_KP_0:
                return ImGuiKey_Keypad0;
            case GLFW_KEY_KP_1:
                return ImGuiKey_Keypad1;
            case GLFW_KEY_KP_2:
                return ImGuiKey_Keypad2;
            case GLFW_KEY_KP_3:
                return ImGuiKey_Keypad3;
            case GLFW_KEY_KP_4:
                return ImGuiKey_Keypad4;
            case GLFW_KEY_KP_5:
                return ImGuiKey_Keypad5;
            case GLFW_KEY_KP_6:
                return ImGuiKey_Keypad6;
            case GLFW_KEY_KP_7:
                return ImGuiKey_Keypad7;
            case GLFW_KEY_KP_8:
                return ImGuiKey_Keypad8;
            case GLFW_KEY_KP_9:
                return ImGuiKey_Keypad9;
            case GLFW_KEY_KP_DECIMAL:
                return ImGuiKey_KeypadDecimal;
            case GLFW_KEY_KP_DIVIDE:
                return ImGuiKey_KeypadDivide;
            case GLFW_KEY_KP_MULTIPLY:
                return ImGuiKey_KeypadMultiply;
            case GLFW_KEY_KP_SUBTRACT:
                return ImGuiKey_KeypadSubtract;
            case GLFW_KEY_KP_ADD:
                return ImGuiKey_KeypadAdd;
            case GLFW_KEY_KP_ENTER:
                return ImGuiKey_KeypadEnter;
            case GLFW_KEY_KP_EQUAL:
                return ImGuiKey_KeypadEqual;
            case GLFW_KEY_LEFT_SHIFT:
                return ImGuiKey_LeftShift;
            case GLFW_KEY_LEFT_CONTROL:
                return ImGuiKey_LeftCtrl;
            case GLFW_KEY_LEFT_ALT:
                return ImGuiKey_LeftAlt;
            case GLFW_KEY_LEFT_SUPER:
                return ImGuiKey_LeftSuper;
            case GLFW_KEY_RIGHT_SHIFT:
                return ImGuiKey_RightShift;
            case GLFW_KEY_RIGHT_CONTROL:
                return ImGuiKey_RightCtrl;
            case GLFW_KEY_RIGHT_ALT:
                return ImGuiKey_RightAlt;
            case GLFW_KEY_RIGHT_SUPER:
                return ImGuiKey_RightSuper;
            case GLFW_KEY_MENU:
                return ImGuiKey_Menu;
            case GLFW_KEY_0:
                return ImGuiKey_0;
            case GLFW_KEY_1:
                return ImGuiKey_1;
            case GLFW_KEY_2:
                return ImGuiKey_2;
            case GLFW_KEY_3:
                return ImGuiKey_3;
            case GLFW_KEY_4:
                return ImGuiKey_4;
            case GLFW_KEY_5:
                return ImGuiKey_5;
            case GLFW_KEY_6:
                return ImGuiKey_6;
            case GLFW_KEY_7:
                return ImGuiKey_7;
            case GLFW_KEY_8:
                return ImGuiKey_8;
            case GLFW_KEY_9:
                return ImGuiKey_9;
            case GLFW_KEY_A:
                return ImGuiKey_A;
            case GLFW_KEY_B:
                return ImGuiKey_B;
            case GLFW_KEY_C:
                return ImGuiKey_C;
            case GLFW_KEY_D:
                return ImGuiKey_D;
            case GLFW_KEY_E:
                return ImGuiKey_E;
            case GLFW_KEY_F:
                return ImGuiKey_F;
            case GLFW_KEY_G:
                return ImGuiKey_G;
            case GLFW_KEY_H:
                return ImGuiKey_H;
            case GLFW_KEY_I:
                return ImGuiKey_I;
            case GLFW_KEY_J:
                return ImGuiKey_J;
            case GLFW_KEY_K:
                return ImGuiKey_K;
            case GLFW_KEY_L:
                return ImGuiKey_L;
            case GLFW_KEY_M:
                return ImGuiKey_M;
            case GLFW_KEY_N:
                return ImGuiKey_N;
            case GLFW_KEY_O:
                return ImGuiKey_O;
            case GLFW_KEY_P:
                return ImGuiKey_P;
            case GLFW_KEY_Q:
                return ImGuiKey_Q;
            case GLFW_KEY_R:
                return ImGuiKey_R;
            case GLFW_KEY_S:
                return ImGuiKey_S;
            case GLFW_KEY_T:
                return ImGuiKey_T;
            case GLFW_KEY_U:
                return ImGuiKey_U;
            case GLFW_KEY_V:
                return ImGuiKey_V;
            case GLFW_KEY_W:
                return ImGuiKey_W;
            case GLFW_KEY_X:
                return ImGuiKey_X;
            case GLFW_KEY_Y:
                return ImGuiKey_Y;
            case GLFW_KEY_Z:
                return ImGuiKey_Z;
            case GLFW_KEY_F1:
                return ImGuiKey_F1;
            case GLFW_KEY_F2:
                return ImGuiKey_F2;
            case GLFW_KEY_F3:
                return ImGuiKey_F3;
            case GLFW_KEY_F4:
                return ImGuiKey_F4;
            case GLFW_KEY_F5:
                return ImGuiKey_F5;
            case GLFW_KEY_F6:
                return ImGuiKey_F6;
            case GLFW_KEY_F7:
                return ImGuiKey_F7;
            case GLFW_KEY_F8:
                return ImGuiKey_F8;
            case GLFW_KEY_F9:
                return ImGuiKey_F9;
            case GLFW_KEY_F10:
                return ImGuiKey_F10;
            case GLFW_KEY_F11:
                return ImGuiKey_F11;
            case GLFW_KEY_F12:
                return ImGuiKey_F12;
            default:
                return ImGuiKey_None;
        }
    }

    std::shared_ptr<UIPanel> GlfwVulkanUIProvider::CreatePanel(const char* identifier,
                                                               NovelRT::Maths::GeoVector2F position,
                                                               NovelRT::Maths::GeoVector2F scale,
                                                               NovelRT::Graphics::RGBAColour colour)
    {
        auto atom = _factory.GetNext();
        _elements.emplace(atom, std::make_shared<UIPanel>());
        auto newPanel = std::static_pointer_cast<UIPanel>(_elements.at(atom));
        newPanel->Type = UIElementType::Panel;
        newPanel->Colour = colour;
        newPanel->Scale = scale;
        newPanel->Position = position;
        newPanel->Identifer = identifier;
        newPanel->InternalIdentifier = atom;

        return newPanel;
    }
}
