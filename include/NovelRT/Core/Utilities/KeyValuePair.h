// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CORE_UTILITIES_KEYVALUEPAIR_H
#define NOVELRT_CORE_UTILITIES_KEYVALUEPAIR_H

namespace NovelRT::Core::Utilities
{
    template<typename TKey, typename TValueType> class KeyValuePair
    {
    public:
        TKey key;
        TValueType value;
    };
}

#endif //! NOVELRT_CORE_UTILITIES_KEYVALUEPAIR_H
