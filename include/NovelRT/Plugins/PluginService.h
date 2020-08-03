// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_PLUGINS_PLUGINSERVICE_H
#define NOVELRT_PLUGINS_PLUGINSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Plugins {
  using NRTRenderingServiceFactoryCreatorPtr = std::add_pointer<Graphics::IRenderingServiceFactory*()>::type;

  class PluginService {
  private:
    std::map<Atom, NRTPluginPointer> _loadedPlugins;
    PluginInfo getPluginInfo(const std::filesystem::path& path) const;
    NRTPluginPointer loadPlugin(const std::filesystem::path& location);

  public:
    PluginService() noexcept; 

    bool tryGetPluginInfo(const std::filesystem::path& location, PluginInfo& info, bool isRelative = true) const;
    std::vector<PluginInfo> getAllAvailablePluginInfo(const std::filesystem::path& location = "Plugins", bool isRelative = true, bool shouldRecurse = true) const;

    std::shared_ptr<Graphics::IRenderingService> createRenderingService(const PluginInfo& info) noexcept;
    ~PluginService();
  };
}

#endif
