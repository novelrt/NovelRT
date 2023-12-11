// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>

namespace NovelRT::Graphics
{
    GraphicsCmdList::GraphicsCmdList(std::shared_ptr<GraphicsContext> context) noexcept : _context(context)
    {
    }

    std::shared_ptr<GraphicsContext> GraphicsCmdList::GetContext() const noexcept
    {
        return _context;
    }
}