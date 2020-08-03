// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.


#ifndef NOVELRT_PLUGINS_LOADLIBHELPER_H
#define NOVELRT_PLUGINS_LOADLIBHELPER_H
#include <NovelRT.h>

namespace NovelRT::Plugins {
  std::string getLibraryExtension() noexcept;
  NRTPluginPointer loadPluginLibrary(const std::string& target);
  bool freePluginLibrary(NRTPluginPointer target);

  template<typename T>
  T getSymbolForFunctionPtr(NRTPluginPointer lib, const std::string& symbolName) {
#if defined(WIN32) || defined(WIN64)
    return reinterpret_cast<T>(GetProcAddress(lib, symbolName.c_str()));
#else
    return reinterpret_cast<T>(dlsym(lib, symbolName.c_str()));
#endif
  }
}

#endif
