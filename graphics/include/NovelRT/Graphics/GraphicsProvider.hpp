// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSPROVIDER_H
#define NOVELRT_GRAPHICS_GRAPHICSPROVIDER_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
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

        virtual ~GraphicsProvider() = default;
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSPROVIDER_H
