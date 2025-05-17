#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#define unused(x) (void)(x)

#define assert_message(exp, msg) assert((static_cast<void>(msg), exp));
