#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend>
    class ShaderProgram final
        : public GraphicsDeviceObject<TBackend>
    {
    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<ShaderProgram<TBackend>> shared_from_this();

        ~ShaderProgram() noexcept final = default;

        [[nodiscard]] const std::string& GetEntryPointName() const noexcept;

        [[nodiscard]] ShaderProgramKind GetKind() const noexcept;

        [[nodiscard]] NovelRT::Utilities::Span<const uint8_t> GetBytecode() const noexcept;
    };
}
