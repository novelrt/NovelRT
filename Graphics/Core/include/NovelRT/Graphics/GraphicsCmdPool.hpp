#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>
#include <functional>
#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsCmdList;
    template<typename TBackend>
    class GraphicsDevice;

    enum class CommandListLevel
    {
        Primary = 0,
        Secondary = 1
    };

    template<typename TBackend>
    class GraphicsCmdPool : std::enable_shared_from_this<GraphicsCmdPool<TBackend>>
    {
    public:
        GraphicsCmdPool() = delete;
        ~GraphicsCmdPool() = default;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<TBackend>> GetDevice() const noexcept;

        std::shared_ptr<GraphicsCmdList<TBackend>> AllocateCommandList(CommandListLevel level);
    };
}
