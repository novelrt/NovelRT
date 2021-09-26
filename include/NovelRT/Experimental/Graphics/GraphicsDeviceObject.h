// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSDEVICEOBJECT_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSDEVICEOBJECT_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsDeviceObject : public std::enable_shared_from_this<GraphicsDeviceObject>
    {
    private:
        std::weak_ptr<GraphicsDevice> _graphicsDevice;

    public:
        explicit GraphicsDeviceObject(std::weak_ptr<GraphicsDevice> graphicsDevice) noexcept
            : _graphicsDevice(std::move(graphicsDevice))
        {
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsDevice> GetDevice() const
        {
            if (_graphicsDevice.expired())
            {
                throw std::runtime_error("The graphics device has expired!");
            }

            return _graphicsDevice.lock();
        }

        virtual ~GraphicsDeviceObject() = default;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSDEVICEOBJECT_H
