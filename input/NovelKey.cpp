// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Input/NovelKey.hpp>

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

    const std::string& NovelKey::GetKeyName() const noexcept
    {
        return _keyName;
    }

    int32_t NovelKey::GetExternalKeyCode() const noexcept
    {
        return _pairedKey;
    }

    int32_t NovelKey::GetExternalModifierCode() const noexcept
    {
        return _modifier;
    }
}
