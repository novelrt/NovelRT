#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>

#include <chrono>
#include <cstdint>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsFence : public GraphicsDeviceObject<TBackend>
    {
    public:
        GraphicsFence() = delete;
        virtual ~GraphicsFence() noexcept override = default;

        [[nodiscard]] bool GetIsSignalled() const;

        void Reset();

        [[nodiscard]] bool TryWait();
        [[nodiscard]] bool TryWait(uint64_t millisecondsTimeout);
        [[nodiscard]] bool TryWait(std::chrono::duration<uint64_t, std::milli> timeout);

        void Wait();
        void Wait(uint64_t millisecondsTimeout);
        void Wait(std::chrono::duration<uint64_t, std::milli> timeout);
    };
}
