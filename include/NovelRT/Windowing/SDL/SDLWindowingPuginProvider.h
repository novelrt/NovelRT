#ifndef SDL_WINDOWING_PLUGIN_PROVIDER_H
#define SDL_WINDOWING_PLUGIN_PROVIDER_H


#ifndef NOVELRT_WINDOWING_SDL_H
#error NovelRT does not support including types explicitly by default. Please include Windowing.SDL.h instead for the Windowing::SDL namespace subset.
#endif 

namespace NovelRT::Windowing::SDL
{
    class SDLWindowingPluginProvider final : public PluginManagement::IWindowingPluginProvider
    {
    private:
        std::shared_ptr<SDLWindowingDevice> _windowingDevice;

        [[nodiscard]] SDLWindowingDevice* GetWindowingDeviceInternal() override;

    public:
        SDLWindowingPluginProvider() noexcept; 

        [[nodiscard]] inline std::shared_ptr<SDLWindowingDevice> GetWindowingDevice()
        {
            return std::dynamic_pointer_cast<SDLWindowingDevice>(GetWindowingDeviceInternal()->shared_from_this()
        }
    };
}

#endif // ! SDL_WINDOWING_PLUGIN_PROVIDER_H
