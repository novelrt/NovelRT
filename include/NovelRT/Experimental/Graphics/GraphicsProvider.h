// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPROVIDER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPROVIDER_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsProvider
    {
    private:
        bool _debugModeEnabled;

    public:
        static inline const std::string EnableDebugModeSwitchName = "NovelRT::Experimental::Graphics::GraphicsProvider::EnableDebugMode";

        GraphicsProvider() noexcept : _debugModeEnabled(EngineConfig::EnableDebugOutputFromEngineInternals())
        {
        }

        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsAdapter>>::iterator begin() noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsAdapter>>::const_iterator begin() const noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsAdapter>>::const_iterator cbegin() const noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsAdapter>>::iterator end() noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsAdapter>>::const_iterator end() const noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsAdapter>>::const_iterator cend() const noexcept = 0;

        virtual ~GraphicsProvider() = default;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPROVIDER_H
