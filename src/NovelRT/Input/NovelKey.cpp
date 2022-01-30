// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Input/Input.h>
#include <NovelRT/PluginManagement/PluginManagement.h>

namespace NovelRT::Input
{
    NovelKey::NovelKey(std::string keyName, int32_t pairedKeyCode, int32_t modifier) noexcept
    {
        _keyName = keyName;
        _pairedKey = pairedKeyCode;
        _modifier = modifier;
    }

    void NovelKey::PairKey(int32_t externalKeyCode) noexcept
    {
        _pairedKey = externalKeyCode;
    }

    void NovelKey::UnpairKey() noexcept
    {
        _pairedKey = -1;
    }

    std::string& NovelKey::GetKeyName() noexcept
    {
        return _keyName;
    }

    int32_t NovelKey::GetExternalKeyCode() noexcept
    {
        return _pairedKey;
    }

    int32_t NovelKey::GetExternalModifierCode() noexcept
    {
        return _modifier;
    }
}
