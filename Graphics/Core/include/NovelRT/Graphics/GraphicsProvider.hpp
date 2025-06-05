#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <string>
#include <vector>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsAdapter;
    template<typename TBackend>
    struct GraphicsBackendTraits;
    template<typename TBackend>
    class GraphicsProvider;

    template<typename TBackend>
    class GraphicsProvider : public std::enable_shared_from_this<GraphicsProvider<TBackend>>
    {
    public:
        using iterator = typename std::vector<std::shared_ptr<GraphicsAdapter<TBackend>>>::iterator;

    public:
        static inline const std::string EnableDebugModeSwitchName =
            "NovelRT::Graphics::GraphicsProvider::EnableDebugMode";

        GraphicsProvider() = delete;
        virtual ~GraphicsProvider() = default;

        [[nodiscard]] bool GetDebugModeEnabled() const noexcept;

        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator begin() const noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator end() const noexcept;

        [[nodiscard]] uint32_t GetApiVersion() const noexcept;
    };
}
