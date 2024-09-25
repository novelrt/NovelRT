#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/EngineConfig.h>
#include <memory>
#include <vector>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsAdapter;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsProvider : public std::enable_shared_from_this<GraphicsProvider<TBackend>>
    {
    public:
        using BackendProviderType = typename GraphicsBackendTraits<TBackend>::ProviderType;

    private:
        std::shared_ptr<BackendProviderType> _implementation;
        bool _debugModeEnabled;

    public:
        static inline const std::string EnableDebugModeSwitchName =
            "NovelRT::Graphics::GraphicsProvider::EnableDebugMode";

        GraphicsProvider(std::shared_ptr<BackendProviderType> implementation) noexcept
            : _implementation(implementation), _debugModeEnabled(EngineConfig::EnableDebugOutputFromEngineInternals())
        {
        }
        
        virtual ~GraphicsProvider() override = default;

        [[nodiscard]] bool GetDebugModeEnabled() const noexcept
        {
            return _debugModeEnabled;
        }

        [[nodiscard]] typename std::vector<std::shared_ptr<GraphicsAdapter<TBackend>>>::iterator begin() noexcept
        {
            return _implementation->begin();
        }

        [[nodiscard]] typename std::vector<std::shared_ptr<GraphicsAdapter<TBackend>>>::iterator end() noexcept
        {
            return _implementation->end();
        }

        [[nodiscard]] uint32_t GetApiVersion() const noexcept
        {
            return _implementation->GetApiVersion();
        }
    };
}
