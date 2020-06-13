// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

#include <nethost.h>

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

using namespace NovelRT::Utilities;

#if defined(WIN32)
  #define STR(s) L ## s
#else
  #define STR(s) s
#endif

const auto HostApiBufferTooSmall = 0x80008098;

static void* getNativeExport(void* nativeLibrary, const char* exportName) {
#if defined(_WIN32)
  void* nativeExport = GetProcAddress(static_cast<HMODULE>(nativeLibrary), exportName);
  assert(nativeExport != nullptr);
  return nativeExport;
#else
  void* nativeExport = dlsym(nativeLibrary, exportName);
  assert(nativeExport != nullptr);
  return nativeExport;
#endif
}

static void* loadNativeLibrary(const char_t* path)
{
#if defined(_WIN32)
  HMODULE nativeLibrary = LoadLibraryW(path);
  assert(nativeLibrary != nullptr);
  return static_cast<void*>(nativeLibrary);
#else
  void* nativeLibrary = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
  assert(nativeLibrary != nullptr);
  return nativeLibrary;
#endif
}

static void closeNativeLibrary(void* nativeLibrary)
{
#if defined(_WIN32)
  BOOL result = FreeLibrary(static_cast<HMODULE>(nativeLibrary));
  assert(result != FALSE); unused(result);
#else
  int result = dlclose(nativeLibrary);
  assert(result == 0); unused(result);
#endif
}

namespace NovelRT::DotNet {
  RuntimeService::RuntimeService() :
    _hostContextHandle(Lazy<hostfxr_handle>([&, this] {
      hostfxr_handle hostContextHandle = nullptr;

      std::filesystem::path executableDirPath = Utilities::Misc::getExecutableDirPath();
      std::filesystem::path runtimeConfigJsonPath = executableDirPath / "NovelRT.DotNet.runtimeconfig.json";

      const char_t* runtime_config_path = runtimeConfigJsonPath.c_str();

      _logger.logInfo("Initializing the runtime using: " + runtimeConfigJsonPath.string());

      int result = _hostfxr_initialize_for_runtime_config.getActual()(runtime_config_path, nullptr, &hostContextHandle);

      if (result != 0)
      {
        _logger.logError("Failed to initialize the runtime: ", result);
        throw std::runtime_error("Failed to initialize the runtime");
      }

      return hostContextHandle;
    })),
    _hostfxr(Lazy<void*>([&, this] {
      size_t buffer_size;
      int result = get_hostfxr_path(nullptr, &buffer_size, nullptr);

      if (result != static_cast<int>(HostApiBufferTooSmall))
      {
        _logger.logError("Failed to locate hostfxr: ", result);
        throw std::runtime_error("Failed to locate hostfxr");
      }

      auto buffer = std::vector<char_t>(buffer_size);
      result = get_hostfxr_path(buffer.data(), &buffer_size, nullptr);

      if (result != 0)
      {
        _logger.logError("Failed to locate hostfxr: ", result);
        throw std::runtime_error("Failed to locate hostfxr");
      }

      return loadNativeLibrary(buffer.data());
    })),
    _hostfxr_initialize_for_runtime_config(Lazy<hostfxr_initialize_for_runtime_config_fn>([&, this] {
      return reinterpret_cast<hostfxr_initialize_for_runtime_config_fn>(getNativeExport(_hostfxr.getActual(), "hostfxr_initialize_for_runtime_config"));
    })),
    _hostfxr_get_runtime_delegate(Lazy<hostfxr_get_runtime_delegate_fn>([&, this] {
      return reinterpret_cast<hostfxr_get_runtime_delegate_fn>(getNativeExport(_hostfxr.getActual(), "hostfxr_get_runtime_delegate"));
    })),
    _hostfxr_close(Lazy<hostfxr_close_fn>([&, this] {
      return reinterpret_cast<hostfxr_close_fn>(getNativeExport(_hostfxr.getActual(), "hostfxr_close"));
    })),
    _load_assembly_and_get_function_pointer(Lazy<load_assembly_and_get_function_pointer_fn>([&, this] {
      void* load_assembly_and_get_function_pointer = nullptr;
      int result = _hostfxr_get_runtime_delegate.getActual()(_hostContextHandle.getActual(), hdt_load_assembly_and_get_function_pointer, &load_assembly_and_get_function_pointer);

      if (result != 0)
      {
        _logger.logError("Failed to initialize the runtime: ", result);
        throw std::runtime_error("Failed to initialize the runtime");
      }

      return reinterpret_cast<load_assembly_and_get_function_pointer_fn>(load_assembly_and_get_function_pointer);
    })),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_DOTNET)) {
  }

  RuntimeService::~RuntimeService() {
    if (_hostContextHandle.isCreated())
    {
      int result = _hostfxr_close.getActual()(_hostContextHandle.getActual());
      assert(result == 0); unused(result);
    }

    if (_hostfxr.isCreated())
    {
      closeNativeLibrary(_hostfxr.getActual());
    }
  }

  void RuntimeService::initialize() {
    auto initializeFunction = getFunction<void()>(STR("NovelRT.DotNet.dll"), STR("NovelRT.DotNet.RuntimeService, NovelRT.DotNet"), STR("Initialize"), STR("System.Action, System.Private.Corelib"));
    initializeFunction();
  }
}
