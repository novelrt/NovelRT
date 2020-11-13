// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/Ink/NrtStory.h"
#include "NovelRT.h"

using namespace NovelRT;

#ifdef __cplusplus
extern "C" {
#endif

  NrtBool Nrt_Story_canContinue(NrtStory story) {
    Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
    if(cStory->CanContinue()) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  void Nrt_Story_chooseChoiceIndex(NrtStory story, int choiceIdx) {
    Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
    cStory->ChooseChoiceIndex(choiceIdx);
  }

  NrtResult Nrt_Story_continue(NrtStory story, const char** outputString) {
    if(outputString == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
    *outputString = cStory->Continue();
    return NRT_SUCCESS;
  }

  NrtResult Nrt_Story_continueMaximally(NrtStory story, const char** outputString) {
    if(outputString == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
    *outputString = cStory->ContinueMaximally();
    return NRT_SUCCESS;
  }

  void Nrt_Story_resetState(NrtStory story) {
    Ink::Story* cStory = reinterpret_cast<Ink::Story*>(story);
    cStory->ResetState();
  }

#ifdef __cplusplus
}
#endif
