// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_LOGLEVEL_H
#define NOVELRT_INTEROP_LOGLEVEL_H

#ifdef __cplusplus
extern "C" {
#endif

//Mapped to the values from spdlog.
typedef enum {
    NOVELRT_LOGLEVEL_DEBUG = 1,
    NOVELRT_LOGLEVEL_INFO = 2,
    NOVELRT_LOGLEVEL_WARN = 3,
    NOVELRT_LOGLEVEL_ERR  = 4,
    NOVELRT_LOGLEVEL_OFF = 6
} NrtLogLevel;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_LOGLEVEL_H
