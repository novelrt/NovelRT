// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSMEMORYBUDGET_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSMEMORYBUDGET_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsMemoryBudget
    {
    private:
        size_t _estimatedBudget;
        size_t _estimatedUsage;
        size_t _totalAllocatedRegionSize;
        size_t _totalBlocksSize;

    public:
        GraphicsMemoryBudget(size_t estimatedBudget,
                             size_t estimatedUsage,
                             size_t totalAllocatedRegionSize,
                             size_t totalBlocksSize) noexcept
            : _estimatedBudget(estimatedBudget),
              _estimatedUsage(estimatedUsage),
              _totalAllocatedRegionSize(totalAllocatedRegionSize),
              _totalBlocksSize(totalBlocksSize)
        {
        }

        [[nodiscard]] inline size_t GetEstimatedBudget() const noexcept
        {
            return _estimatedBudget;
        }

        [[nodiscard]] inline size_t GetEstimatedUsage() const noexcept
        {
            return _estimatedUsage;
        }

        [[nodiscard]] inline size_t GetTotalAllocatedRegionSize() const noexcept
        {
            return _totalAllocatedRegionSize;
        }

        [[nodiscard]] inline size_t GetTotalBlocksSize() const noexcept
        {
            return _totalBlocksSize;
        }
    };
} 

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSMEMORYBUDGET_H
