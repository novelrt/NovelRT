#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>

#include <chrono>
#include <cstdint>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsSemaphore : public GraphicsDeviceObject<TBackend>
    {
    public:
        GraphicsSemaphore() = delete;
        virtual ~GraphicsSemaphore() noexcept override = default;

        [[nodiscard]] uint64_t GetValue() const;

        void Signal(uint64_t value);

        bool Wait(uint64_t value);
        bool Wait(uint64_t value, uint64_t millisecondsTimeout);
        bool Wait(uint64_t value, std::chrono::duration<uint64_t, std::milli> timeout);
    };
}
