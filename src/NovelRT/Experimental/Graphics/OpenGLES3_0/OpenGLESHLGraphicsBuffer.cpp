// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/NotSupportedException.h>
#include <NovelRT/Experimental/Graphics/OpenGLES3_0/OpenGLESHLGraphicsBuffer.h>

namespace NovelRT::Experimental::Graphics::OpenGLES3_0
{
    gsl::span<std::byte> OpenGLESHLGraphicsBuffer::MapUntyped(GraphicsResourceCpuAccessKind accessMode)
    {
        if (accessMode > GetEnabledAccessMode() || accessMode == GraphicsResourceCpuAccessKind::None)
        {
            throw Exceptions::NotSupportedException(
                "This resource does not support the specified access mode for mapping.");
        }

        GLbitfield mode = GL_READ_ONLY;
        switch (accessMode)
        {
            case GraphicsResourceCpuAccessKind::None:
                throw std::runtime_error("It should be impossible to see this.");
                break;
            case GraphicsResourceCpuAccessKind::Read:
                mode = GL_READ_ONLY;
                break;
            case GraphicsResourceCpuAccessKind::Write:
                mode = GL_WRITE_ONLY;
                break;
            case GraphicsResourceCpuAccessKind::ReadWrite:
                mode = GL_READ_WRITE;
                break;
            default:
                throw Exceptions::NotSupportedException(
                    "This resource does not support the specified access mode for mapping.");
        }
        GLint output = 0;
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &output);
        return gsl::span<std::byte>(static_cast<std::byte*>(glMapBuffer(GL_ARRAY_BUFFER, mode)), output);
    }

    gsl::span<std::byte> OpenGLESHLGraphicsBuffer::MapRangeUntyped(GraphicsResourceCpuAccessKind accessMode,
                                                                   size_t offset,
                                                                   size_t range)
    {
        if (accessMode > GetEnabledAccessMode() || accessMode == GraphicsResourceCpuAccessKind::None)
        {
            throw Exceptions::NotSupportedException(
                "This resource does not support the specified access mode for mapping.");
        }

        GLbitfield mode = GL_READ_ONLY;
        switch (accessMode)
        {
            case GraphicsResourceCpuAccessKind::None:
                throw std::runtime_error("It should be impossible to see this.");
                break;
            case GraphicsResourceCpuAccessKind::Read:
                mode = GL_READ_ONLY;
                break;
            case GraphicsResourceCpuAccessKind::Write:
                mode = GL_WRITE_ONLY;
                break;
            case GraphicsResourceCpuAccessKind::ReadWrite:
                mode = GL_READ_WRITE;
                break;
            default:
                throw Exceptions::NotSupportedException(
                    "This resource does not support the specified access mode for mapping.");
        }

        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        return gsl::span<std::byte>(
            static_cast<std::byte*>(glMapBufferRange(GL_ARRAY_BUFFER, offset, range, mode)), sizeof(std::byte) * range);

    }

    std::shared_ptr<LLGraphicsResource> OpenGLESHLGraphicsBuffer::GetLLResourceUntyped() const
    {
        throw Exceptions::NotSupportedException();
    }

    void OpenGLESHLGraphicsBuffer::Unmap()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

} // namespace NovelRT::Experimental::Graphics::OpenGLES3_0