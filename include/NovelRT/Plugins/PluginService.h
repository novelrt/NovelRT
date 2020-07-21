// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_PLUGINS_PLUGINSERVICE_H
#define NOVELRT_PLUGINS_PLUGINSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Plugins {
#if defined(WIN32) || defined(WIN64)
  using NRTPluginPointer = HMODULE;
#else
  using NRTPluginPointer = void*;
#endif

  using NRTRenderingServiceCreatorPtr = std::add_pointer<Graphics::IRenderingService*(NovelRunner* const)>::type;

  class PluginService {
  private:
    NovelRunner* const _runner;
    std::map<Atom, NRTPluginPointer> _loadedPlugins;
    PluginInfo getPluginInfo(const std::filesystem::path& path) const;
    NRTPluginPointer loadPlugin(const std::filesystem::path& location);

  public:
    PluginService() noexcept; //TODO: gdi Matt clean these constructors up later
    PluginService(NovelRunner* const runner) noexcept;

    bool tryGetPluginInfo(const std::filesystem::path& location, PluginInfo& info, bool isRelative = true) const;
    std::vector<PluginInfo> getAllAvailablePluginInfo(const std::filesystem::path& location = "Plugins", bool isRelative = true, bool shouldRecurse = true) const;

    std::shared_ptr<Graphics::IRenderingService> createRenderingService(const PluginInfo& info) noexcept;
  };
}

#endif
