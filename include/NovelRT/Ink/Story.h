// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INK_STORY_H
#define NOVELRT_INK_STORY_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Ink
{
    class Story
    {
    private:
        struct Exports
        {
            intptr_t (*CreateFromJsonString)(const char* jsonString);
            void (*ChooseChoiceIndex)(intptr_t storyHandle, int32_t choiceIdx);
            const char* (*Continue)(intptr_t storyHandle);
            const char* (*ContinueMaximally)(intptr_t storyHandle);
            bool (*GetCanContinue)(intptr_t storyHandle);
            void (*ResetState)(intptr_t storyHandle);
        };

        std::shared_ptr<InkService> _inkService;
        Utilities::Lazy<Exports> _exports;
        Utilities::Lazy<intptr_t> _handle;

    public:
        Story(std::shared_ptr<InkService> inkService,
              void (*getExports)(Exports* exports),
              const char* jsonString) noexcept;

        bool CanContinue();

        void ChooseChoiceIndex(int32_t choiceIdx);

        const char* Continue();
        const char* ContinueMaximally();

        void ResetState();

        friend class InkService;
    };
} 

#endif // NOVELRT_INK_STORY_H
