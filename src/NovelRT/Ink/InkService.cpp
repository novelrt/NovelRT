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
    InkService::InkService(std::shared_ptr<DotNet::RuntimeService> runtimeService,
                           void (*getExports)(Exports* exports)) noexcept
        : _runtimeService(runtimeService), _exports(Lazy<Exports>([getExports, this] {
              Exports exports;
              getExports(&exports);
              return exports;
          }))
    {
    }

    void InkService::initialise()
    {
        _exports.getActual().Initialise();
    }

    void InkService::tearDown()
    {
        if (_exports.isCreated())
        {
            _exports.getActual().Teardown();
        }
    }

    std::shared_ptr<Story> InkService::createStory(const char* jsonString)
    {
        return std::make_shared<Story>(shared_from_this(), _exports.getActual().GetStoryExports, jsonString);
    }

    std::shared_ptr<DotNet::RuntimeService> InkService::getRuntimeService()
    {
        return _runtimeService;
    }
} // namespace NovelRT::Ink

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
