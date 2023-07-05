#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>

namespace NovelRT::Graphics
{
    class ShaderProgram : public GraphicsDeviceObject
    {
    private:
        std::string _entryPointName;
        ShaderProgramKind _kind;

    public:
        ShaderProgram(std::shared_ptr<GraphicsDevice> device,
                      std::string entryPointName,
                      ShaderProgramKind kind) noexcept;

        [[nodiscard]] inline const std::string& GetEntryPointName() const noexcept
        {
            return _entryPointName;
        }

        [[nodiscard]] inline ShaderProgramKind GetKind() const noexcept
        {
            return _kind;
        }

        [[nodiscard]] virtual NovelRT::Utilities::Misc::Span<const uint8_t> GetBytecode() const noexcept = 0;
    };
}
