// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Graphics.hpp>

namespace NovelRT::Graphics
{

    ShaderProgram::ShaderProgram(std::shared_ptr<GraphicsDevice> device,
                                 std::string entryPointName,
                                 ShaderProgramKind kind) noexcept
        : GraphicsDeviceObject(std::move(device)), _entryPointName(std::move(entryPointName)), _kind(kind)
    {
    }
} // namespace NovelRT::Graphics
