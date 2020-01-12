// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_RuntimeService_H
#define NOVELRT_RuntimeService_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::DotNet {
  class RuntimeService {
  private:
    NovelRT::Utilities::Lazy<hostfxr_handle> _hostContextHandle;
    NovelRT::Utilities::Lazy<void*> _hostfxr;
    NovelRT::Utilities::Lazy<hostfxr_initialize_for_runtime_config_fn> _hostfxr_initialize_for_runtime_config;
    NovelRT::Utilities::Lazy<hostfxr_get_runtime_delegate_fn> _hostfxr_get_runtime_delegate;
    NovelRT::Utilities::Lazy<hostfxr_close_fn> _hostfxr_close;
    NovelRT::Utilities::Lazy<load_assembly_and_get_function_pointer_fn> _load_assembly_and_get_function_pointer;

  public:
    RuntimeService();
    ~RuntimeService();

    template <class _Fty>
    std::function<_Fty> getFunction(const char_t* assemblyName, const char_t* typeName, const char_t* methodName, const char_t* delegateTypeName) {
      std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
      std::filesystem::path assemblyPath = executableDirPath / assemblyName;

#if defined(WIN32)
      const char_t* assembly_path = assemblyPath .c_str();
#else
      const char_t* assembly_path = assemblyPath.string().c_str();
#endif

      void* delegate;
      int result = _load_assembly_and_get_function_pointer.getActual()(assembly_path, typeName, methodName, delegateTypeName, nullptr, &delegate);

      if (result != 0)
      {
        std::cerr << "ERROR: failed to locate the specified managed function" << std::endl;
        throw - 1;
      }

      return std::function<_Fty>(static_cast<_Fty*>(delegate));
    }

    void initialize();
  };
}

#endif
