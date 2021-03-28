// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ink/NrtStory.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

using namespace NovelRT;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtBool Nrt_Story_canContinue(NrtStoryHandle story)
    {
        Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
        if (cStory->CanContinue())
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    void Nrt_Story_chooseChoiceIndex(NrtStoryHandle story, int32_t choiceIdx)
    {
        Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
        cStory->ChooseChoiceIndex(choiceIdx);
    }

    const char* Nrt_Story_continue(NrtStoryHandle story)
    {
        Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
        return cStory->Continue();
    }

    const char* Nrt_Story_continueMaximally(NrtStoryHandle story)
    {
        Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
        return cStory->ContinueMaximally();
    }

    void Nrt_Story_resetState(NrtStoryHandle story)
    {
        Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
        cStory->ResetState();
    }

#ifdef __cplusplus
}
#endif
