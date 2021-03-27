// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
//#include "stdint.h"

#ifndef NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H
#define NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtKeyState Nrt_KeyStateFrameChangeLog_getCurrentState(NrtKeyStateFrameChangeLogHandle changeLog);

    uint32_t Nrt_KeyStateFrameChangeLog_getChangeCount(NrtKeyStateFrameChangeLogHandle changeLog);

    NrtBool Nrt_KeyStateFrameChangeLog_compareChangeLog(NrtKeyStateFrameChangeLogHandle lhs, NrtKeyState rhs);
    NrtBool Nrt_KeyStateFrameChangeLog_compareKeyState(NrtKeyState lhs, NrtKeyStateFrameChangeLogHandle rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_KEYSTATEFRAMECHANGELOG_H
