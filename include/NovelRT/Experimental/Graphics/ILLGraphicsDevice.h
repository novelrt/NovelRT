// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ILLGRAPHICSDEVICE_H
#define NOVELRT_ILLGRAPHICSDEVICE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class ILLGraphicsDevice
    {
    public:
        virtual void Initialise(std::shared_ptr<IGraphicsSurface> targetSurface) = 0;
        virtual void TearDown() = 0;
        [[nodiscard]] virtual std::shared_ptr<ShaderProgram> CreateShaderProgram(gsl::span<std::byte> byteData) = 0;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_ILLGRAPHICSDEVICE_H
