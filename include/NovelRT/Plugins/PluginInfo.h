// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_PLUGINS_PLUGININFO_H
#define NOVELRT_PLUGINS_PLUGININFO_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Plugins {
  class PluginInfo {
  private:
    Atom _pluginId;
    PluginKind _kind;
    std::filesystem::path _fullPathLocation;
    std::string _engineVersion;
    std::string _pluginInfoVersion;

  public:
    PluginInfo(Atom pluginId, PluginKind kind, const std::filesystem::path& fullPathLocation, const std::string& engineVersion, const std::string& pluginInfoVersion) noexcept :
      _pluginId(pluginId),
      _kind(kind),
      _fullPathLocation(fullPathLocation),
      _engineVersion(engineVersion),
      _pluginInfoVersion(pluginInfoVersion){}

    inline Atom PluginId() const noexcept {
      return _pluginId;
    }

    inline PluginKind Kind() const noexcept {
      return _kind;
    }

    inline const std::filesystem::path& fullPathLocation() const noexcept {
      return _fullPathLocation;
    }

    inline const std::string& engineVersion() const noexcept {
      return _engineVersion;
    }

    inline const std::string& pluginInfoVersion() const noexcept {
      return _pluginInfoVersion;
    }

  };
}


#endif
