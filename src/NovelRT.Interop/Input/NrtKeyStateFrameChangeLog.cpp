// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Input/NrtKeyStateFrameChangeLog.h>

#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtKeyState Nrt_KeyStateFrameChangeLog_getCurrentState(NrtKeyStateFrameChangeLogHandle changeLog)
    {
        Input::KeyStateFrameChangeLog& log = reinterpret_cast<Input::KeyStateFrameChangeLog&>(changeLog);
        auto state = log.getCurrentState();
        return reinterpret_cast<NrtKeyState&>(state);
    }

    uint32_t Nrt_KeyStateFrameChangeLog_getChangeCount(NrtKeyStateFrameChangeLogHandle changeLog)
    {
        Input::KeyStateFrameChangeLog& log = reinterpret_cast<Input::KeyStateFrameChangeLog&>(changeLog);
        return log.getChangeCount();
    }

    NrtBool Nrt_KeyStateFrameChangeLog_compareChangeLog(NrtKeyStateFrameChangeLogHandle lhs, NrtKeyState rhs)
    {
        Input::KeyStateFrameChangeLog& log = reinterpret_cast<Input::KeyStateFrameChangeLog&>(lhs);
        auto keyState = reinterpret_cast<const Input::KeyState&>(rhs);

        if (log == keyState)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_KeyStateFrameChangeLog_compareKeyState(NrtKeyState lhs, NrtKeyStateFrameChangeLogHandle rhs)
    {
        return Nrt_KeyStateFrameChangeLog_compareChangeLog(rhs, lhs);
    }

#ifdef __cplusplus
}
#endif
