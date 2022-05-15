// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_DIALOGUENODE_H
#define NOVELRT_DIALOGUENODE_H

namespace NovelRT::Narrative
{
    struct DialogueNode
    {
        std::optional<std::string> text;
        std::optional<std::function<void()>> callbackAtTextStart; // TODO: idk if we need these two callbacks
        std::optional<std::function<void()>> callbackAtTextEnd;
        std::optional<std::vector<DialogueChoice>> dialogueChoices;
    };
}

#endif // NOVELRT_DIALOGUENODE_H
