// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_DIALOGUECHOICE_H
#define NOVELRT_DIALOGUECHOICE_H

namespace NovelRT::Narrative
{
    struct DialogueChoice
    {
        std::string text;
        std::optional<std::function<void()>> callbackOnExecute; // TODO: idk if we need this
        std::string nextSectionToExecute;
    };
}

#endif // NOVELRT_DIALOGUECHOICE_H
