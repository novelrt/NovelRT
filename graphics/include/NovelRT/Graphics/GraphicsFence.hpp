#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>

namespace NovelRT::Graphics
{
    class GraphicsFence : public GraphicsDeviceObject
    {
    public:
        explicit GraphicsFence(std::weak_ptr<GraphicsDevice> device) noexcept : GraphicsDeviceObject(std::move(device))
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

        inline void Wait()
        {
            Wait(std::numeric_limits<uint64_t>::max());
        }

        inline void Wait(uint64_t millisecondsTimeout)
        {
            if (!TryWait(millisecondsTimeout))
            {
                throw Exceptions::TimeoutException(millisecondsTimeout);
            }
        }

        inline void Wait(std::chrono::duration<uint64_t, std::milli> timeout)
        {
            if (!TryWait(timeout))
            {
                throw Exceptions::TimeoutException(timeout.count());
            }
        }
    };
}
