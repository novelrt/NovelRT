// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSADAPTER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSADAPTER_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsAdapter
    {
    private:
        std::shared_ptr<GraphicsProvider> _provider;

    public:
        explicit GraphicsAdapter(std::shared_ptr<GraphicsProvider> provider) :
        _provider(std::move(provider))
        {
            if (_provider == nullptr)
            {
                throw Exceptions::NullPointerException("The provided GraphicsProvider pointer is nullptr.");
            }
        }

        [[nodiscard]] virtual uint32_t GetDeviceId() const noexcept = 0;

        [[nodiscard]] virtual const std::string& GetName() const noexcept = 0;

        [[nodiscard]] inline std::shared_ptr<GraphicsProvider> GetProvider() const noexcept
        {
            return _provider;
        }

        virtual ~GraphicsAdapter() = default;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSADAPTER_H
