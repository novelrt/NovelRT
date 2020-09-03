#include <stdio.h>
#include <stdint.h>
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/NovelRTNovelRunner.h"
#include "NovelRT.Interop/Input/NovelRTInteractionService.h"
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"

const char* error = " ";
NovelRTResult res = NOVELRT_SUCCESS;
NovelRTBool booleanResult = NOVELRT_TRUE;
NovelRTAudioService audio = NULL;
NovelRTInteractionService input = NULL;

void inputTest(NovelRTTimestamp delta) {
    NovelRTKeyStateFrameChangeLog in = NULL;
    res = NovelRT_InteractionService_getKeyState(input, W, &in, &error);
    if (res == NOVELRT_SUCCESS) {
        if (NovelRT_KeyStateFrameChangeLog_compareKeyState(KeyDown, in) == NOVELRT_TRUE) {
            fprintf(stdout, "W was pressed! \n");
            float vn = NovelRT_Timestamp_getSecondsFloat(delta);
            fprintf(stdout, "Timestamp: %f", vn);
        }
    }
    else {
        fprintf(stderr, error);
    }
}

int main() {
    
    NovelRTNovelRunner* runner = NovelRunner_create(0);

    res = NovelRT_NovelRunner_getAudioService(runner, &audio, &error);
    if (res == NOVELRT_FAILURE) {
        fprintf(stderr, "Error:");
        fprintf(stderr, error);
        return -1;
    }
    else {
        res = NovelRT_AudioService_initialiseAudio(audio, &booleanResult, &error);
        if (res == NOVELRT_SUCCESS) {
            fprintf(stdout, "\nInitialised Audio from C API!\n");
        }
        else {
            fprintf(stderr, "Error:");
            fprintf(stderr, error);
        }   
    }


    res = NovelRT_NovelRunner_getInteractionService(runner, &input, &error);
    if (res == NOVELRT_FAILURE) {
        fprintf(stderr, "Error:");
        fprintf(stderr, error);
        return -1;
    }
    else {
       fprintf(stdout, "\nInitialised Input from C API!\n");
    }


    void (*test)(NovelRTTimestamp);
    test = &inputTest;

    NovelRT_NovelRunner_addUpdate(runner, test, &error);

    NovelRunner_runNovel(runner);

    return 0;
}

