// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSDEVICEOBJECT_H
#define NOVELRT_GRAPHICSDEVICEOBJECT_H

#include <memory>

namespace NovelRT::Experimental::Graphics
{
    class ILLGraphicsDevice;
    class GraphicsDeviceObject
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
    };
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_GRAPHICSDEVICEOBJECT_H
