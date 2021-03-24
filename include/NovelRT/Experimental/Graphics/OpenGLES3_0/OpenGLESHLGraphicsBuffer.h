// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_OPENGLESHLGRAPHICSBUFFER_H
#define NOVELRT_OPENGLESHLGRAPHICSBUFFER_H

#include "../HLGraphicsBuffer.h"
#include <glad/glad.h>

namespace NovelRT::Experimental::Graphics::OpenGLES3_0
{
    class OpenGLESHLGraphicsBuffer : public HLGraphicsBuffer
    {
    private:
        GLuint _bufferId = 0;

        [[nodiscard]] GLbitfield ValidateAndTranslateAccessMode(GraphicsResourceCpuAccessKind accessMode) const;

    public:
        explicit OpenGLESHLGraphicsBuffer(GraphicsResourceCpuAccessKind accessKind) noexcept
            : HLGraphicsBuffer(accessKind)
        {
        }

        [[nodiscard]] gsl::span<std::byte> MapUntyped(GraphicsResourceCpuAccessKind accessMode) final;
        [[nodiscard]] gsl::span<std::byte> MapRangeUntyped(GraphicsResourceCpuAccessKind accessMode,
                                                           size_t offset,
                                                           size_t range) final;
        [[nodiscard]] std::shared_ptr<LLGraphicsResource> GetLLResourceUntyped() const final;
        void Unmap() final;
    };
} // namespace NovelRT::Experimental::Graphics::OpenGLES3_0

#endif // NOVELRT_OPENGLESHLGRAPHICSBUFFER_H
