// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_INK_STORY_H
#define NOVELRT_INTEROP_INK_STORY_H

#include "../NrtInteropUtils.h"
#include "../DotNet/NrtRuntimeTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//NrtInkStory Nrt_InkStory_createStory(NrtInkService service, void(*getExports)(Exports* exports), const char* jsonString)
  NrtBool Nrt_Story_canContinue(NrtStory story);
  void Nrt_Story_chooseChoiceIndex(NrtStory story, int choiceIdx);
  NrtResult Nrt_Story_continue(NrtStory story, const char** outputString);
  NrtResult Nrt_Story_continueMaximally(NrtStory story, const char** outputString);
  void Nrt_Story_resetState(NrtStory story);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INK_INKSERVICE_H
