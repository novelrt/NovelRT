#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class ShaderProgram : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendShaderProgramType = typename GraphicsBackendTraits<TBackend>::ShaderProgramType;

    private:
        std::unique_ptr<BackendShaderProgramType> _implementation;
        std::string _entryPointName;
        ShaderProgramKind _kind;

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<ShaderProgram<TBackend>> shared_from_this()
        {
            return std::static_pointer_cast<ShaderProgram<TBackend>>(GraphicsDeviceObject<TBackend>::shared_from_this());
        }

        ShaderProgram(std::unique_ptr<BackendShaderProgramType> implementation,
                      std::shared_ptr<GraphicsDevice<TBackend>> device,
                      std::string entryPointName,
                      ShaderProgramKind kind) noexcept
            : GraphicsDeviceObject<TBackend>(std::move(device))
            , _implementation(std::move(implementation))
            , _entryPointName(std::move(entryPointName))
            , _kind(kind)
        {
        }

        virtual ~ShaderProgram() noexcept override = default;

        [[nodiscard]] BackendShaderProgramType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }

        [[nodiscard]] const std::string& GetEntryPointName() const noexcept
        {
            return _entryPointName;
        }

        [[nodiscard]] ShaderProgramKind GetKind() const noexcept
        {
            return _kind;
        }

        [[nodiscard]] NovelRT::Utilities::Span<const uint8_t> GetBytecode() const noexcept
        {
            return _implementation->GetBytecode();
        }
    };
}
