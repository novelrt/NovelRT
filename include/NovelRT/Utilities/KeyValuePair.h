// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UTILITIES_KEYVALUEPAIR_H
#define NOVELRT_UTILITIES_KEYVALUEPAIR_H

namespace NovelRT::Utilities
{
    template<typename TKey, typename TValueType> class KeyValuePair
    {
    public:
        TKey key;
        TValueType value;
    };
} // namespace NovelRT::Utilities

#endif //! NOVELRT_UTILITIES_KEYVALUEPAIR_H
