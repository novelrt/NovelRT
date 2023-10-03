// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_NOVELKEY_H
#define NOVELRT_INPUT_NOVELKEY_H

#ifndef NOVELRT_INPUT_H
#error NovelRT does not support including types explicitly by default. Please include Input.h instead for the Input namespace subset.
#endif

namespace NovelRT::Input
{
    class NovelKey
    {
    public:
        int32_t _pairedKey;
        std::string _keyName;
        int32_t _modifier;
        NovelKey(std::string keyName = "", int32_t pairedKeyCode = -1, int32_t modifier = 0) noexcept;
        void PairKey(int32_t externalKeyCode) noexcept;
        void UnpairKey() noexcept;
        [[nodiscard]] const std::string& GetKeyName() const noexcept;
        [[nodiscard]] int32_t GetExternalKeyCode() const noexcept;
        [[nodiscard]] int32_t GetExternalModifierCode() const noexcept;

        [[nodiscard]] inline bool operator==(NovelKey& other) noexcept
        {
            return (_keyName == other.GetKeyName()) && (_pairedKey == other.GetExternalKeyCode());
        };
    };

    inline bool operator==(NovelKey const& lhs, NovelKey const& rhs) noexcept
    {
        return lhs._pairedKey == rhs._pairedKey && (lhs._modifier == rhs._modifier) && lhs._keyName == rhs._keyName;
    }

    inline bool operator!=(NovelKey const& lhs, NovelKey const& rhs) noexcept
    {
        return lhs._pairedKey != rhs._pairedKey || (lhs._modifier == rhs._modifier) || lhs._keyName == rhs._keyName;
    }
}

#endif // NOVELRT_INPUT_NOVELKEY_H
