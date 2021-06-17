// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_LLGRAPHICSRESOURCEVIEWCONTAINER_H
#define NOVELRT_EXPERIMENTAL_LLGRAPHICSRESOURCEVIEWCONTAINER_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    template<typename T> class LLGraphicsResourceViewContainer
    {
    private:
        std::shared_ptr<LLGraphicsResource> _ptr;

    public:
        LLGraphicsResourceViewContainer(std::shared_ptr<LLGraphicsResource> ptr) noexcept : _ptr(std::move(ptr))
        {
        }

        [[nodiscard]] constexpr T* operator ->()
        {
            return reinterpret_cast<T*>(_ptr.get());
        }
    };
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_EXPERIMENTAL_LLGRAPHICSRESOURCEVIEWCONTAINER_H
