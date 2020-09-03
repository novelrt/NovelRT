#include <stdio.h>
#include <stdint.h>
#include <memory.h>
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/NovelRTNovelRunner.h"
#include "NovelRT.Interop/Input/NovelRTInteractionService.h"
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/Timing/NovelRTStepTimer.h"
#include "NovelRT.Interop/Utilities/NovelRTEvents.h"
#include "NovelRT.Interop/NovelRTLoggingService.h"

const char* error = " ";
NovelRTResult res = NOVELRT_SUCCESS;
NovelRTBool booleanResult = NOVELRT_TRUE;
NovelRTAudioService audio = NULL;
NovelRTInteractionService input = NULL;
NovelRTLoggingService console = NULL;
NovelRTStepTimer timer = NULL;
NovelRTUpdateEventWithTimestamp updateEvent = NULL;

void inputTest(NovelRTTimestamp delta) {    
    NovelRTKeyStateFrameChangeLog in = NULL;
    res = NovelRT_InteractionService_getKeyState(input, W, &in, &error);
    if (res == NOVELRT_SUCCESS) {
        if (NovelRT_KeyStateFrameChangeLog_compareKeyState(KeyDown, in) == NOVELRT_TRUE) {
            NovelRT_LoggingService_logInfoLine(console, "W was pressed!", &error);
            float vn = NovelRT_Timestamp_getSecondsFloat(delta);
            //Need to find a way for variadic messages in NovelRT_LoggingService
            fprintf(stdout, "Timestamp: %f \r\n", vn);
        }
    }
    else {
        char* errMsg = error;
        NovelRT_LoggingService_logErrorLine(console, errMsg, &error);
    }
}

void timerTest(NovelRTTimestamp delta) {
    uint32_t fps = 0;
    res = NovelRT_StepTimer_getFramesPerSecond(timer, &fps, &error);
    NovelRT_Timestamp_getSecondsFloat(delta);
    if (res == NOVELRT_SUCCESS) {
        fprintf(stdout, "FPS: %f \n", (double)(fps));
    }
}

int main() {
    
    NovelRTNovelRunner runner = NovelRT_NovelRunner_create(0);
    
    console = NovelRT_LoggingService_createCustomTitle("Interop");

    res = NovelRT_NovelRunner_getAudioService(runner, &audio, &error);
    if (res == NOVELRT_FAILURE) {
        char* precursor = "Error getting AudioService: ";
        char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
        strcpy(errMsg, precursor);
        strcpy(errMsg, error);
        NovelRT_LoggingService_logErrorLine(console, errMsg, &error);
        return -1;
    }
    else {
        res = NovelRT_LoggingService_throwIfNullPtr(console, &audio, "AudioService was not returned properly! Exiting...", &error);
        res = NovelRT_AudioService_initialiseAudio(audio, &booleanResult, &error);
        if (res == NOVELRT_SUCCESS) {
            NovelRT_LoggingService_logInfoLine(console, "Initialised Audio from C API!", &error);
        }
        else {
            char* precursor = "Error initialising Audio: ";
            char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
            strcpy(errMsg, precursor);
            strcpy(errMsg, error);
            NovelRT_LoggingService_logErrorLine(console, errMsg, &error);
        }   
    }

    res = NovelRT_NovelRunner_getInteractionService(runner, &input, &error);
    if (res == NOVELRT_SUCCESS) {
        NovelRT_LoggingService_logInfoLine(console, "Received InteractionService from C API!", &error);
    }
    else {
       char* precursor = "Error getting InteractionService: ";
            char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
            strcpy(errMsg, precursor);
            strcpy(errMsg, error);
            NovelRT_LoggingService_logErrorLine(console, errMsg, &error);
            return -1;
    }

    res = NovelRT_StepTimer_create(60.0, 0.1, &timer, &error);
    res = NovelRT_Events_getNovelRunnerUpdateEvent(runner, &updateEvent, &error);

    NovelRT_StepTimer_tick(timer, updateEvent, &error);
    
    NovelRT_NovelRunner_addUpdate(runner, &inputTest, &error);
    //NovelRT_NovelRunner_addUpdate(runner, &timerTest, &error);

    NovelRT_NovelRunner_runNovel(runner, &error);

    return 0;
}

