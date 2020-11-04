// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Input/NrtKeyStateFrameChangeLog.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

int32_t Nrt_KeyStateFrameChangeLog_getCurrentState(NrtKeyStateFrameChangeLog changeLog, NrtKeyState* output) {
    Input::KeyStateFrameChangeLog& log = reinterpret_cast<Input::KeyStateFrameChangeLog&>(changeLog);

    if (output == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    auto state = log.getCurrentState();
    *output = reinterpret_cast<NrtKeyState&>(state);
    return NRT_SUCCESS;
}

int32_t Nrt_KeyStateFrameChangeLog_getChangeCount(NrtKeyStateFrameChangeLog changeLog, uint32_t* output) {
    Input::KeyStateFrameChangeLog& log = reinterpret_cast<Input::KeyStateFrameChangeLog&>(changeLog);
    
    if (output == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    *output = log.getChangeCount();
    return NRT_SUCCESS;
}

int32_t Nrt_KeyStateFrameChangeLog_compareChangeLog(NrtKeyStateFrameChangeLog lhs, NrtKeyState rhs) {
    Input::KeyStateFrameChangeLog& log = reinterpret_cast<Input::KeyStateFrameChangeLog&>(lhs);
    auto keyState = reinterpret_cast<const Input::KeyState&>(rhs);

    if (log == keyState) {
        return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t Nrt_KeyStateFrameChangeLog_compareKeyState(NrtKeyState lhs, NrtKeyStateFrameChangeLog rhs) {
    return Nrt_KeyStateFrameChangeLog_compareChangeLog(rhs, lhs);
}

#ifdef __cplusplus
}
#endif