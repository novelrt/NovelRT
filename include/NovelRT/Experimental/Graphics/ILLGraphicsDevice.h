// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ILLGRAPHICSDEVICE_H
#define NOVELRT_ILLGRAPHICSDEVICE_H

#include <string>
#include <vector>

namespace NovelRT::Experimental::Graphics
{
    class ILLGraphicsDevice
    {
    public:
        virtual void Initialise(std::shared_ptr<IGraphicsSurface> targetSurface) = 0;
        virtual void TearDown() = 0;
    };
}

#endif // NOVELRT_ILLGRAPHICSDEVICE_H