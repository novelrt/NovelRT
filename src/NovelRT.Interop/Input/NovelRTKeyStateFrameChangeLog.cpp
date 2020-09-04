// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"
#include "NovelRT.Interop/Input/NovelRTKeyStateFrameChangeLog.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

int32_t NovelRT_KeyStateFrameChangeLog_getCurrentState(NovelRTKeyStateFrameChangeLog changeLog, NovelRTKeyState* output, const char** errorMessage) {
    Input::KeyStateFrameChangeLog& log = reinterpret_cast<Input::KeyStateFrameChangeLog&>(changeLog);
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    auto state = log.getCurrentState();
    *output = reinterpret_cast<NovelRTKeyState&>(state);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_KeyStateFrameChangeLog_getChangeCount(NovelRTKeyStateFrameChangeLog changeLog, uint32_t* output, const char** errorMessage) {
    Input::KeyStateFrameChangeLog& log = reinterpret_cast<Input::KeyStateFrameChangeLog&>(changeLog);
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    *output = log.getChangeCount();
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_KeyStateFrameChangeLog_compareChangeLog(NovelRTKeyStateFrameChangeLog lhs, NovelRTKeyState rhs) {
    Input::KeyStateFrameChangeLog& log = reinterpret_cast<Input::KeyStateFrameChangeLog&>(lhs);
    auto keyState = reinterpret_cast<const Input::KeyState&>(rhs);
    if (log == keyState) {
        return NOVELRT_TRUE;
    }
    return NOVELRT_FALSE;
}

int32_t NovelRT_KeyStateFrameChangeLog_compareKeyState(NovelRTKeyState lhs, NovelRTKeyStateFrameChangeLog rhs) {
    return NovelRT_KeyStateFrameChangeLog_compareChangeLog(rhs, lhs);
}

#ifdef __cplusplus
}
#endif