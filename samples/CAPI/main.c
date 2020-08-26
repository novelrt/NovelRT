#include <stdio.h>
#include <stdint.h>
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/NovelRTNovelRunner.h"
#include "NovelRT.Interop/Input/NovelRTInteractionService.h"

int main() {
    const char* error = " ";
    NovelRTResult res = NOVELRT_SUCCESS;
    NovelRTBool booleanResult = NOVELRT_TRUE;
    
    
    NovelRTNovelRunner* runner = NovelRunner_create(0);
    NovelRTAudioService audio = NULL;
    NovelRTInteractionService input = NULL;

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


    NovelRunner_runNovel(runner);

    return 0;
}