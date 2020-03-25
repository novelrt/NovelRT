// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_PLUGINS_PLUGINSERVICE_H
#define NOVELRT_PLUGINS_PLUGINSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Plugins {
#if defined(WIN32) || defined(WIN64)
  typedef HMODULE NRTPluginPointer;
#else
  typedef void* NRTPluginPointer;
#endif

  class PluginService {
  private:
    std::map<Atom, std::shared_ptr<NRTPluginPointer>> _loadedPlugins;
    PluginInfo getPluginInfo(const std::filesystem::path& info) const;
    NRTPluginPointer loadPlugin(const std::filesystem::path& location);

  public:
    bool tryGetPluginInfo(const std::filesystem::path& path, PluginInfo& info, bool isRelative = true) const noexcept;
    std::vector<PluginInfo> getAllAvailablePluginInfo(const std::filesystem::path& location = "Plugins", bool isRelative = true, bool shouldRecurse = true) noexcept;

    template<typename TPluginInterface>
    std::shared_ptr<TPluginInterface> getPlugin(const PluginInfo& info) const noexcept {
      
    }
  };
}


#endif
