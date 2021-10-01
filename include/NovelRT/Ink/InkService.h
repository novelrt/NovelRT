// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INK_INKSERVICE_H
#define NOVELRT_INK_INKSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Ink
{
    class InkService : public std::enable_shared_from_this<InkService>
    {
    private:
        struct Exports
        {
            void (*Initialise)();
            void (*Teardown)();
            void (*GetStoryExports)(struct Story::Exports* exports);
        };

        std::shared_ptr<DotNet::RuntimeService> _runtimeService;
        Utilities::Lazy<Exports> _exports;

    public:
        InkService(std::shared_ptr<DotNet::RuntimeService> runtimeService,
                   void (*getExports)(Exports* exports)) noexcept;

        void initialise();
        void tearDown();

        std::shared_ptr<Story> createStory(const char* jsonString);

        std::shared_ptr<DotNet::RuntimeService> getRuntimeService() noexcept;

        friend class NovelRT::DotNet::RuntimeService;
    };
}

#endif // NOVELRT_TIMING_STEPTIMER_H
