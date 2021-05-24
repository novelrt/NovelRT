// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSFENCE_H
#define NOVELRT_GRAPHICSFENCE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsFence : public GraphicsDeviceObject
    {
    public:
        GraphicsFence(std::shared_ptr<ILLGraphicsDevice> device) noexcept : GraphicsDeviceObject(device)
        {
        }

        [[nodiscard]] virtual bool GetIsSignalled() = 0;
        virtual void Reset() = 0;
        [[nodiscard]] virtual bool TryWait(uint64_t millisecondsTimeout) noexcept = 0;
        [[nodiscard]] virtual bool TryWait(std::chrono::duration<uint64_t, std::milli> timeout) noexcept = 0;

        void Wait(uint64_t millisecondsTimeout)
        {
            if (!TryWait(millisecondsTimeout))
            {
                throw std::runtime_error("TODO: Replace me!");
            }
        }

        void Wait(std::chrono::duration<uint64_t, std::milli> timeout)
        {
            if (!TryWait(timeout))
            {
                throw std::runtime_error("TODO: Replace me!");
            }
        }
    };
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_GRAPHICSFENCE_H
