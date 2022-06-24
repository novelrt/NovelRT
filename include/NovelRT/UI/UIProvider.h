// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIPROVIDER_H
#define NOVELRT_UI_UIPROVIDER_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the UI namespace subset.
#endif

namespace NovelRT::UI
{
    class UIProvider : public std::enable_shared_from_this<UIProvider>
    {
    public:
        UIProvider() noexcept
        {
        }

        virtual void Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                                std::shared_ptr<Input::IInputDevice> inputDevice) = 0;

        virtual void BeginFrame(double deltaTime) = 0;

        virtual void EndFrame() = 0;

        virtual ~UIProvider() = default;
    };
}

#endif // !NOVELRT_UI_UIPROVIDER_H
