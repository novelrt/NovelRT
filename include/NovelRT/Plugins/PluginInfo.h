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
    std::string _name;
    PluginKind _kind;
    std::filesystem::path _location;
    std::string _engineVersion;
    std::string _pluginInfoVersion;

  public:
    PluginInfo(Atom pluginId, const std::string& name, PluginKind kind, const std::filesystem::path& fullPathLocation, const std::string& engineVersion, const std::string& pluginInfoVersion) noexcept :
      _pluginId(pluginId),
      _name(name),
      _kind(kind),
      _location(fullPathLocation),
      _engineVersion(engineVersion),
      _pluginInfoVersion(pluginInfoVersion){}

    PluginInfo() noexcept :
      _pluginId(uintptr_t(0)),
      _name(""),
      _kind(PluginKind::UnknownOrInvalid),
      _location(""),
      _engineVersion(""),
      _pluginInfoVersion("") {}

    inline const Atom& PluginId() const noexcept {
      return _pluginId;
    }

    inline const std::string& Name() const noexcept {
      return _name;
    }

    inline const PluginKind& Kind() const noexcept {
      return _kind;
    }

    inline const std::filesystem::path& location() const noexcept {
      return _location;
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
