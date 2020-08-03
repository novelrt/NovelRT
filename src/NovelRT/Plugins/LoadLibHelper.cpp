#include "LoadLibHelper.h"

namespace NovelRT::Plugins {

  std::string getLibraryExtension() noexcept {
#if defined(WIN32) || defined(WIN64)
    return ".dll";
#elif defined(__linux__)
    return ".so";
#elif defined(__APPLE__)
    return ".dylib";
#endif
  }

  NRTPluginPointer loadPluginLibrary(const std::string& target) {
#if defined(WIN32) || defined(WIN64)
    return LoadLibrary(target.c_str());
#else
    return dlopen(target.c_str(), RTLD_NOW);
#endif
  }

  bool freePluginLibrary(NRTPluginPointer target) {
#if defined(WIN32) || defined(WIN64)
  return !FreeLibrary(target);
#else
  return dlclose(target);
#endif
  }
}
