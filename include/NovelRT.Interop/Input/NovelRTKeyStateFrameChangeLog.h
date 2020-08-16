// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Input/NovelRTKeyState.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
//#include "stdint.h"

#ifndef NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H
#define NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ChangeLogHandle* NovelRTKeyStateFrameChangeLog;

NovelRTResult NovelRT_KeyStateFrameChangeLog_getCurrentState(NovelRTKeyStateFrameChangeLog changeLog, NovelRTKeyState* output, const char** errorMessage);

NovelRTResult NovelRT_KeyStateFrameChangeLog_getChangeCount(NovelRTKeyStateFrameChangeLog changeLog, uint32_t* output, const char** errorMessage);

NovelRTBool NovelRT_KeyStateFrameChangeLog_compareChangeLog(NovelRTKeyStateFrameChangeLog lhs, NovelRTKeyState rhs);
NovelRTBool NovelRT_KeyStateFrameChangeLog_compareKeyState(NovelRTKeyState lhs, NovelRTKeyStateFrameChangeLog rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H