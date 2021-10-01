// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ANIMATION_SPRITEANIMATORFRAME_H
#define NOVELRT_ANIMATION_SPRITEANIMATORFRAME_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Animation
{
    class SpriteAnimatorFrame
    {
    public:
        Utilities::Event<> FrameEnter;
        Utilities::Event<> FrameExit;

    private:
        std::shared_ptr<Graphics::Texture> _texture;
        Timing::Timestamp _duration;

    public:
        SpriteAnimatorFrame() noexcept : _duration(Timing::Timestamp::zero())
        {
        }

        inline const std::shared_ptr<Graphics::Texture>& texture() const noexcept
        {
            return _texture;
        }

        inline std::shared_ptr<Graphics::Texture>& texture() noexcept
        {
            return _texture;
        }

        inline const Timing::Timestamp& duration() const noexcept
        {
            return _duration;
        }

        inline Timing::Timestamp& duration() noexcept
        {
            return _duration;
        }
    };
} 

#endif //! NOVELRT_ANIMATION_SPRITEANIMATORFRAME_H
