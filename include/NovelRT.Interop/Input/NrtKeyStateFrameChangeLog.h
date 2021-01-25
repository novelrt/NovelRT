// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
//#include "stdint.h"

#ifndef NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H
#define NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H

#include "../NrtInteropUtils.h"
#include "NrtKeyState.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct ChangeLogHandle* NrtKeyStateFrameChangeLog;

    NrtKeyState Nrt_KeyStateFrameChangeLog_getCurrentState(NrtKeyStateFrameChangeLog changeLog);

    uint32_t Nrt_KeyStateFrameChangeLog_getChangeCount(NrtKeyStateFrameChangeLog changeLog);

    NrtBool Nrt_KeyStateFrameChangeLog_compareChangeLog(NrtKeyStateFrameChangeLog lhs, NrtKeyState rhs);
    NrtBool Nrt_KeyStateFrameChangeLog_compareKeyState(NrtKeyState lhs, NrtKeyStateFrameChangeLog rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H
