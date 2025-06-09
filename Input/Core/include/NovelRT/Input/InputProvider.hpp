#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Input/InputAction.hpp>
#include <NovelRT/Input/KeyState.hpp>
#include <NovelRT/Input/KeyStateFrameChangeLog.hpp>
#include <NovelRT/Input/NovelKey.hpp>
#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Timing/Timestamp.hpp>
#include <NovelRT/Utilities/Span.hpp>
#include <NovelRT/Windowing/WindowProvider.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace NovelRT::Input
{
    template<typename TBackend>
    class InputProvider
    {
    public:
        InputProvider() = delete;

        void Update(Timing::Timestamp::duration delta);
        [[nodiscard]] bool IsKeyPressed(const std::string& key);
        [[nodiscard]] bool IsKeyHeld(const std::string& key);
        [[nodiscard]] bool IsKeyReleased(const std::string& key);
        [[nodiscard]] KeyState GetKeyState(const std::string& key);
        [[nodiscard]] InputAction& AddInputAction(const std::string& actionName, const std::string& keyIdentifier);
        [[nodiscard]] NovelKey& GetAvailableKey(const std::string& keyRequested);
        [[nodiscard]] InputAction* FindInputActionForKey(const std::string& keyRequested);
        [[nodiscard]] NovelRT::Maths::GeoVector2F GetMousePosition();
        [[nodiscard]] NovelRT::Maths::GeoVector2F GetRawMousePosition();
        [[nodiscard]] NovelRT::Utilities::Span<InputAction> GetAllMappings();
        [[nodiscard]] KeyStateFrameChangeLog GetCurrentChangeLog(const std::string& key);
        [[nodiscard]] KeyStateFrameChangeLog GetPreviousChangeLog(const std::string& key);
        [[nodiscard]] NovelRT::Utilities::Span<std::unordered_map<int32_t, KeyStateFrameChangeLog>> GetAllChangeLogs();
    };
}
