// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NARRATIVE_H
#define NOVELRT_NARRATIVE_H

// dependencies
#include <filesystem>
#include <string>
#include <optional>
#include <functional>
#include <vector>
#include <gsl/span>

namespace NovelRT::Narrative
{
    class Story;
    struct DialogueNode;
    struct DialogueChoice;
}

// clang-format off
#include "Story.h"
#include "DialogueNode.h"
#include "DialogueChoice.h"
// clang-format on

#endif // NOVELRT_NARRATIVE_H
