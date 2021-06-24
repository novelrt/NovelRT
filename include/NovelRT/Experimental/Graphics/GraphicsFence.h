#include <utility>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSFENCE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSFENCE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsFence : public GraphicsDeviceObject
    {
    public:
        explicit GraphicsFence(std::shared_ptr<GraphicsDevice> device) noexcept : GraphicsDeviceObject(std::move(device))
        {
        }

        [[nodiscard]] virtual bool GetIsSignalled() = 0;
        virtual void Reset() = 0;

        [[nodiscard]] inline bool TryWait()
        {
            return TryWait(std::numeric_limits<uint64_t>::max());
        }

        [[nodiscard]] virtual bool TryWait(uint64_t millisecondsTimeout) = 0;
        [[nodiscard]] virtual bool TryWait(std::chrono::duration<uint64_t, std::milli> timeout) = 0;

        void Wait(uint64_t millisecondsTimeout)
        {
            if (!TryWait(millisecondsTimeout))
            {
                throw Exceptions::TimeoutException(millisecondsTimeout);
            }
        }

        void Wait(std::chrono::duration<uint64_t, std::milli> timeout)
        {
            if (!TryWait(timeout))
            {
                throw Exceptions::TimeoutException(timeout.count());
            }
        }
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSFENCE_H
