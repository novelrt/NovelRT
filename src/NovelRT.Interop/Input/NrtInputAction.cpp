// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Input/NrtInputAction.h>
#include <NovelRT.Interop/Input/NrtNovelKey.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Input/Input.h>

using namespace NovelRT::Input;

NrtInputActionInfo Nrt_InputAction_ReadAsInfo(NrtInputActionHandle action)
{
    auto* inputAction = reinterpret_cast<InputAction*>(action);
    return NrtInputActionInfo{inputAction->actionName.c_str(),
                              Nrt_NovelKey_ReadAsInfo(reinterpret_cast<NrtNovelKeyHandle>(&inputAction->pairedKey)),
                              static_cast<NrtKeyState>(inputAction->state)};
}
intptr_t Nrt_InputActionList_IncrementSize()
{
    return sizeof(InputAction);
}

const char* Nrt_InputAction_GetActionName(NrtInputActionHandle action)
{
    return reinterpret_cast<InputAction*>(action)->actionName.c_str();
}
NrtNovelKeyHandle Nrt_InputAction_GetPairedKey(NrtInputActionHandle action)
{
    return reinterpret_cast<NrtNovelKeyHandle>(&reinterpret_cast<InputAction*>(action)->pairedKey);
}
NrtKeyState Nrt_InputAction_GetState(NrtInputActionHandle action)
{
    return static_cast<NrtKeyState>(reinterpret_cast<InputAction*>(action)->state);
}
