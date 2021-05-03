// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSDEVICEOBJECT_H
#define NOVELRT_GRAPHICSDEVICEOBJECT_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsDeviceObject : public std::enable_shared_from_this<GraphicsDeviceObject>
    {
    private:
        std::shared_ptr<ILLGraphicsDevice> _graphicsDevice;

    public:
        explicit GraphicsDeviceObject(std::shared_ptr<ILLGraphicsDevice> graphicsDevice) noexcept
            : _graphicsDevice(std::move(graphicsDevice))
        {
        }

        [[nodiscard]] inline std::shared_ptr<ILLGraphicsDevice> GetDevice() const noexcept
        {
            return _graphicsDevice;
        }

        virtual ~GraphicsDeviceObject() = default;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_GRAPHICSDEVICEOBJECT_H
