// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_WINDOWING_IWINDOWINGDEVICE_H
#define NOVELRT_WINDOWING_IWINDOWINGDEVICE_H

#ifndef NOVELRT_WINDOWING_H
#error NovelRT does not support including types explicitly by default. Please include Windowing.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::Windowing
{
    class IWindowingDevice : public Graphics::IGraphicsSurface, public std::enable_shared_from_this<IWindowingDevice>
    {
    public:
        virtual void Initialise(NovelRT::Windowing::WindowMode windowMode, Maths::GeoVector2F desiredWindowSize) = 0;
        virtual void TearDown() noexcept = 0;
        virtual void ProcessAllMessages() = 0;
        [[nodiscard]] virtual bool GetIsVisible() const noexcept = 0;
        [[nodiscard]] virtual bool GetShouldClose() const noexcept = 0;
        [[nodiscard]] virtual std::string GetWindowTitle() const noexcept = 0;
        virtual void SetWindowTitle(const std::string& newTitle) = 0;

        virtual ~IWindowingDevice() = default;
    };
}

#endif // NOVELRT_WINDOWING_IWINDOWINGDEVICE_H
