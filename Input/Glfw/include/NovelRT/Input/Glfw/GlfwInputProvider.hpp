#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Input/InputProvider.hpp>
#include <NovelRT/Logging/LoggingService.hpp>

#include <cstdint>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

// TODO: Figure out if this is required
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace NovelRT::Input::Glfw
{
    struct GlfwInputBackend;
}

namespace NovelRT::Windowing::Glfw
{
    struct GlfwWindowingBackend;
}

namespace NovelRT::Input
{
    template<>
    class InputProvider<Glfw::GlfwInputBackend>
    {
    private:
        static const uint32_t DefaultBufferCount = 6;

        std::shared_ptr<Windowing::WindowProvider<Windowing::Glfw::GlfwWindowingBackend>> _windowProvider;
        std::vector<InputAction> _previousStates;
        std::vector<InputAction> _mappedActions;
        std::map<std::string, NovelKey> _availableKeys;
        std::vector<std::unordered_map<int32_t, KeyStateFrameChangeLog>> _keyStates;

        NovelRT::Maths::GeoVector2F _mousePos;
        NovelRT::Maths::GeoVector2F _rawMousePos;
        NovelRT::Maths::GeoVector2F _windowDimensions;

        uint32_t _previousBufferIndex;
        uint32_t _currentBufferIndex;

        Logging::LoggingService _logger;

        void ProcessKeyInput(int32_t key, int32_t action);
        void ProcessCursorMovement(NovelRT::Maths::GeoVector2F& pos);
        void ProcessKeyState(int32_t action, KeyState state);
        NovelRT::Maths::GeoVector2F DetermineMouseScreenPosition(NovelRT::Maths::GeoVector2F& pos);
        void MapAllGlfwKeysToNovelKeys();

    public:
        InputProvider(std::shared_ptr<Windowing::WindowProvider<Windowing::Glfw::GlfwWindowingBackend>> windowProvider);
        ~InputProvider() = default;

        void Update(NovelRT::Timing::Timestamp::duration delta);
        [[nodiscard]] bool IsKeyPressed(const std::string& input) noexcept;
        [[nodiscard]] bool IsKeyHeld(const std::string& input) noexcept;
        [[nodiscard]] bool IsKeyReleased(const std::string& input) noexcept;
        [[nodiscard]] KeyState GetKeyState(const std::string& key) noexcept;
        [[nodiscard]] InputAction& AddInputAction(const std::string& actionName, const std::string& keyIdentifier);
        [[nodiscard]] NovelKey& GetAvailableKey(const std::string& keyRequested);
        [[nodiscard]] InputAction* FindInputActionForKey(const std::string& keyRequested);
        [[nodiscard]] NovelRT::Maths::GeoVector2F GetMousePosition() noexcept;
        [[nodiscard]] NovelRT::Maths::GeoVector2F GetRawMousePosition() noexcept;
        [[nodiscard]] NovelRT::Utilities::Span<InputAction> GetAllMappings() noexcept;
        [[nodiscard]] KeyStateFrameChangeLog GetCurrentChangeLog(const std::string& key);
        [[nodiscard]] KeyStateFrameChangeLog GetPreviousChangeLog(const std::string& key);
        [[nodiscard]] NovelRT::Utilities::Span<std::unordered_map<int32_t, KeyStateFrameChangeLog>> GetAllChangeLogs();
    };
}
