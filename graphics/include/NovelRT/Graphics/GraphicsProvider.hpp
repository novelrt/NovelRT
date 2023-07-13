#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <vector>
#include <NovelRT/EngineConfig.h>

namespace NovelRT::Graphics
{
    class GraphicsAdapter;

    class GraphicsProvider : public std::enable_shared_from_this<GraphicsProvider>
    {
    private:
        bool _debugModeEnabled;

    public:
        static inline const std::string EnableDebugModeSwitchName =
            "NovelRT::Graphics::GraphicsProvider::EnableDebugMode";

        GraphicsProvider() noexcept : _debugModeEnabled(EngineConfig::EnableDebugOutputFromEngineInternals())
        {
        }

        [[nodiscard]] inline bool GetDebugModeEnabled() const noexcept
        {
            return _debugModeEnabled;
        }

        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsAdapter>>::iterator begin() noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsAdapter>>::iterator end() noexcept = 0;
        [[nodiscard]] virtual uint32_t GetApiVersion() const noexcept = 0;

        virtual ~GraphicsProvider() = default;
    };
}
