#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>

#include <chrono>
#include <cstdint>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsFence : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendFenceType = typename GraphicsBackendTraits<TBackend>::FenceType;

    private:
        std::unique_ptr<BackendFenceType> _implementation;

    public:
        GraphicsFence(std::unique_ptr<BackendFenceType> implementation, std::weak_ptr<GraphicsDevice<TBackend>> device) noexcept
            : GraphicsDeviceObject<TBackend>(std::move(device))
            , _implementation(std::move(implementation))
        {
        }

        virtual ~GraphicsFence() noexcept override = default;

        [[nodiscard]] BackendFenceType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }

        [[nodiscard]] bool GetIsSignalled()
        {
            return _implementation->GetIsSignalled();
        }

        void Reset()
        {
            _implementation->Reset();
        }

        [[nodiscard]] bool TryWait()
        {
            return TryWait(std::numeric_limits<uint64_t>::max());
        }

        [[nodiscard]] bool TryWait(uint64_t millisecondsTimeout)
        {
            return _implementation->TryWait(millisecondsTimeout);
        }

        [[nodiscard]] bool TryWait(std::chrono::duration<uint64_t, std::milli> timeout)
        {
            return _implementation->TryWait(timeout);
        }

        void Wait()
        {
            _implementation->Wait();
        }
    };
}
