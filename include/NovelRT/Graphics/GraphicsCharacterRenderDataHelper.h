// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSCHARACTERRENDERDATAHELPER_H
#define NOVELRT_GRAPHICS_GRAPHICSCHARACTERRENDERDATAHELPER_H

namespace NovelRT::Graphics
{
    class GraphicsCharacterRenderDataHelper
    {
    public:
        static inline int32_t getAdvanceDistance(FT_Pos rawAdvanceDistance) noexcept
        {
            return static_cast<int32_t>(rawAdvanceDistance);
        }
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSCHARACTERRENDERDATAHELPER_H
