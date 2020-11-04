// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
//#include "stdint.h"

#ifndef NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H
#define NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H

#include "NrtKeyState.h"
#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ChangeLogHandle* NrtKeyStateFrameChangeLog;

int32_t Nrt_KeyStateFrameChangeLog_getCurrentState(NrtKeyStateFrameChangeLog changeLog, NrtKeyState* output);

int32_t Nrt_KeyStateFrameChangeLog_getChangeCount(NrtKeyStateFrameChangeLog changeLog, uint32_t* output);

int32_t Nrt_KeyStateFrameChangeLog_compareChangeLog(NrtKeyStateFrameChangeLog lhs, NrtKeyState rhs);
int32_t Nrt_KeyStateFrameChangeLog_compareKeyState(NrtKeyState lhs, NrtKeyStateFrameChangeLog rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H