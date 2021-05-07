// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RuntimeService_H
#define NOVELRT_RuntimeService_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::DotNet
{
    class RuntimeService : public std::enable_shared_from_this<RuntimeService>
    {
    private:
        struct Exports
        {
            void (*Initialise)();
            void (*Teardown)();
            void (*FreeObject)(intptr_t obj);
            void (*FreeString)(const char* str);
            void (*GetInkServiceExports)(struct Ink::InkService::Exports* exports);
        };

        Utilities::Lazy<hostfxr_handle> _hostContextHandle;
        Utilities::Lazy<void*> _hostfxr;
        Utilities::Lazy<hostfxr_initialize_for_runtime_config_fn> _hostfxr_initialize_for_runtime_config;
        Utilities::Lazy<hostfxr_get_runtime_delegate_fn> _hostfxr_get_runtime_delegate;
        Utilities::Lazy<hostfxr_close_fn> _hostfxr_close;
        Utilities::Lazy<load_assembly_and_get_function_pointer_fn> _load_assembly_and_get_function_pointer;
        Utilities::Lazy<Exports> _exports;
        LoggingService _logger;
        std::string get_hostfxr_string(std::vector<char_t> buffer) noexcept;

    public:
        RuntimeService();
        ~RuntimeService();

        void initialise() noexcept;
        void tearDown() noexcept;

        void freeObject(intptr_t obj) noexcept;
        void freeString(const char* str) noexcept;

        std::shared_ptr<Ink::InkService> getInkService() noexcept;
    };
} // namespace NovelRT::DotNet

#endif
