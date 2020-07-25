// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_RuntimeService_H
#define NOVELRT_RuntimeService_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::DotNet {
  class RuntimeService {
  private:
    Utilities::Lazy<hostfxr_handle> _hostContextHandle;
    Utilities::Lazy<void*> _hostfxr;
    Utilities::Lazy<hostfxr_initialize_for_runtime_config_fn> _hostfxr_initialize_for_runtime_config;
    Utilities::Lazy<hostfxr_get_runtime_delegate_fn> _hostfxr_get_runtime_delegate;
    Utilities::Lazy<hostfxr_close_fn> _hostfxr_close;
    Utilities::Lazy<load_assembly_and_get_function_pointer_fn> _load_assembly_and_get_function_pointer;
    LoggingService _logger;

  public:
    RuntimeService();
    ~RuntimeService();

    template <class _Fty>
    std::function<_Fty> getFunction(const char_t* assemblyName, const char_t* typeName, const char_t* methodName, const char_t* delegateTypeName) {
      std::filesystem::path executableDirPath = Utilities::Misc::getExecutableDirPath();
      std::filesystem::path assemblyPath = executableDirPath / assemblyName;

      const char_t* assembly_path = assemblyPath .c_str();

      void* delegate;
      int result = _load_assembly_and_get_function_pointer.getActual()(assembly_path, typeName, methodName, delegateTypeName, nullptr, &delegate);

      if (result != 0)
      {
        _logger.logError("Failed to locate the specified managed function: {}", result);
        throw std::runtime_error("Failed to locate the specified managed function");
      }

      return std::function<_Fty>(reinterpret_cast<_Fty*>(delegate));
    }

    void initialize();
  };
}

#endif
