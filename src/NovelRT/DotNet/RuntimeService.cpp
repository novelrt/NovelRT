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
  #define CH(c) L ## c
#else
  #define STR(s) s
  #define CH(c) c
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
  assert(result != FALSE);
#else
  int result = dlclose(nativeLibrary);
  assert(result == 0);
#endif
}

static void* loadHostFxr() {
  size_t buffer_size;
  int result = get_hostfxr_path(nullptr, &buffer_size, nullptr);

  if (result != HostApiBufferTooSmall)
  {
    std::cerr << "ERROR: failed to locate hostfxr" << std::endl;
    throw - 1;
  }

  auto buffer = std::vector<char_t>(buffer_size);
  result = get_hostfxr_path(buffer.data(), &buffer_size, nullptr);

  if (result != 0)
  {
    std::cerr << "ERROR: failed to locate hostfxr" << std::endl;
    throw - 1;
  }

  return loadNativeLibrary(buffer.data());
}

namespace NovelRT::DotNet {
  RuntimeService::RuntimeService() :
    _hostContextHandle(Lazy<hostfxr_handle>([&, this] {
      hostfxr_handle hostContextHandle = nullptr;

      std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
      std::filesystem::path runtimeConfigJsonPath = executableDirPath / "NovelRT.DotNet.runtimeconfig.json";

#if defined(WIN32)
      const char_t* runtime_config_path = runtimeConfigJsonPath.c_str();
#else
      const char_t* runtime_config_path = runtimeConfigJsonPath.string().c_str();
#endif

      int result = _hostfxr_initialize_for_runtime_config.getActual()(runtime_config_path, nullptr, &hostContextHandle);

      if (result != 0)
      {
        std::cerr << "ERROR: failed to initialize the runtime" << std::endl;
        throw -1;
      }

      return hostContextHandle;
    })),
    _hostfxr(Lazy<void*>(std::function(loadHostFxr))),
    _hostfxr_initialize_for_runtime_config(Lazy<hostfxr_initialize_for_runtime_config_fn>([&, this] {
      return static_cast<hostfxr_initialize_for_runtime_config_fn>(getNativeExport(_hostfxr.getActual(), "hostfxr_initialize_for_runtime_config"));
    })),
    _hostfxr_get_runtime_delegate(Lazy<hostfxr_get_runtime_delegate_fn>([&, this] {
      return static_cast<hostfxr_get_runtime_delegate_fn>(getNativeExport(_hostfxr.getActual(), "hostfxr_get_runtime_delegate"));
    })),
    _hostfxr_close(Lazy<hostfxr_close_fn>([&, this] {
      return static_cast<hostfxr_close_fn>(getNativeExport(_hostfxr.getActual(), "hostfxr_close"));
    })),
    _load_assembly_and_get_function_pointer(Lazy<load_assembly_and_get_function_pointer_fn>([&, this] {
      void* load_assembly_and_get_function_pointer = nullptr;
      int result = _hostfxr_get_runtime_delegate.getActual()(_hostContextHandle.getActual(), hdt_load_assembly_and_get_function_pointer, &load_assembly_and_get_function_pointer);

      if (result != 0)
      {
        std::cerr << "ERROR: failed to initialize the runtime" << std::endl;
        throw -1;
      }

      return static_cast<load_assembly_and_get_function_pointer_fn>(load_assembly_and_get_function_pointer);
    })) {
  }

  RuntimeService::~RuntimeService() {
    if (_hostContextHandle.isCreated())
    {
      int result = _hostfxr_close.getActual()(_hostContextHandle.getActual());
      assert(result == 0);
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
