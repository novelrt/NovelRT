// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Input/NrtNovelKey.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Input/Input.h>

using namespace NovelRT::Input;

NrtNovelKeyInfo Nrt_NovelKey_ReadAsInfo(NrtNovelKeyHandle key)
{
    auto* novelKey = reinterpret_cast<NovelRT::Input::NovelKey*>(key);
    return NrtNovelKeyInfo{novelKey->GetKeyName().c_str(), novelKey->GetExternalKeyCode(),
                           novelKey->GetExternalModifierCode()};
}

const char* Nrt_NovelKey_GetKeyName(NrtNovelKeyHandle key)
{
    return reinterpret_cast<NovelRT::Input::NovelKey*>(key)->GetKeyName().c_str();
}

int32_t Nrt_NovelKey_GetExternalKeyCode(NrtNovelKeyHandle key)
{
    return reinterpret_cast<NovelRT::Input::NovelKey*>(key)->GetExternalKeyCode();
}

int32_t Nrt_NovelKey_GetExternalModifierCode(NrtNovelKeyHandle key)
{
    return reinterpret_cast<NovelRT::Input::NovelKey*>(key)->GetExternalModifierCode();
}

NrtResult Nrt_NovelKey_PairKey(NrtNovelKeyHandle key, int32_t externalKeyCode)
{
    if (key == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* novelKey = reinterpret_cast<NovelRT::Input::NovelKey*>(key);
    novelKey->PairKey(externalKeyCode);

    return NRT_SUCCESS;
}

NrtResult Nrt_NovelKey_UnpairKey(NrtNovelKeyHandle key)
{
    if (key == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* novelKey = reinterpret_cast<NovelRT::Input::NovelKey*>(key);
    novelKey->UnpairKey();

    return NRT_SUCCESS;
}

NrtBool Nrt_NovelKey_equal(NrtNovelKeyHandle lhs, NrtNovelKeyHandle rhs)
{
    return *reinterpret_cast<NovelKey*>(lhs) == *reinterpret_cast<NovelKey*>(rhs);
}
