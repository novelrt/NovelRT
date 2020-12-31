// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-lambda-capture"
#endif

#include <NovelRT.h>

using namespace NovelRT::Utilities;

namespace NovelRT::Ink
{
    Story::Story(std::shared_ptr<InkService> inkService, void (*getExports)(Exports* exports),
                 const char* jsonString) noexcept
        : _inkService(inkService),
          _exports(Lazy<Exports>([getExports, this] {
              Exports exports;
              getExports(&exports);
              return exports;
          })),
          _handle(Lazy<intptr_t>([jsonString, this] { return _exports.getActual().CreateFromJsonString(jsonString); }))
    {
    }

    bool Story::CanContinue()
    {
        return _exports.getActual().GetCanContinue(_handle.getActual());
    }

    void Story::ChooseChoiceIndex(int32_t choiceIdx)
    {
        _exports.getActual().ChooseChoiceIndex(_handle.getActual(), choiceIdx);
    }

    const char* Story::Continue()
    {
        return _exports.getActual().Continue(_handle.getActual());
    }

    const char* Story::ContinueMaximally()
    {
        return _exports.getActual().ContinueMaximally(_handle.getActual());
    }

    void Story::ResetState()
    {
        _exports.getActual().ResetState(_handle.getActual());
    }
} // namespace NovelRT::Ink

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
