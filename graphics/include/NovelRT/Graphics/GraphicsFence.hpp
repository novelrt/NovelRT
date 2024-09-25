#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsFence : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendFenceType = typename GraphicsBackendTraits<TBackend>::FenceType;

    private:
        std::shared_ptr<BackendFenceType> _implementation;

    public:
        GraphicsFence(std::shared_ptr<BackendFenceType> implementation, std::shared_ptr<GraphicsDevice<TBackend>> device) noexcept
            : GraphicsDeviceObject(device)
        {
        }

        virtual ~GraphicsFence() override = default;

        [[nodiscard]] bool GetIsSignalled()
        {
            return _implementation->GetIsSignalled();
        }

        void Reset()
        {
            _implementation->Reset();
        }

        [[nodiscard]] inline bool TryWait()
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

        inline void Wait()
        {
            Wait(std::numeric_limits<uint64_t>::max());
        }
    };
}
