// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>

#include <utility>

namespace NovelRT::Experimental::Graphics
{

    ShaderProgram::ShaderProgram(std::shared_ptr<GraphicsDevice> device,
                                 std::string entryPointName,
                                 ShaderProgramKind kind) noexcept
        : GraphicsDeviceObject(std::move(device)), _entryPointName(std::move(entryPointName)), _kind(kind)
    {
    }
} // namespace NovelRT::Experimental::Graphics
