#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/NovelRTNovelRunner.h"
#include "NovelRT.Interop/Input/NovelRTInteractionService.h"
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/Timing/NovelRTStepTimer.h"
#include "NovelRT.Interop/Utilities/NovelRTCommonEvents.h"
#include "NovelRT.Interop/NovelRTLoggingService.h"
#include "NovelRT.Interop/Graphics/NovelRTGraphicsTypedefs.h"
#include "NovelRT.Interop/Utilities/NovelRTMisc.h"
#include "NovelRT.Interop/Graphics/NovelRTImageRect.h"

const char* error = " ";
int32_t res = NOVELRT_SUCCESS;
int32_t booleanResult = NOVELRT_TRUE;
int32_t hMove = 1;      // 1 == move right, 0 == move left
int32_t vMove = 1;      // 1 == move up, 0 == move down
NovelRTAudioService audio = NULL;
NovelRTInteractionService input = NULL;
NovelRTLoggingService console = NULL;
NovelRTRuntimeService dotnet = NULL;
NovelRTStepTimer timer = NULL;
NovelRTUtilitiesEventWithTimestamp updateEvent = NULL;
NovelRTRGBAConfig colourChange = NULL;

NovelRTImageRect nChanRect = NULL;

// void inputTest(NovelRTTimestamp delta) {    
//     NovelRTKeyStateFrameChangeLog in = NULL;
//     res = NovelRT_InteractionService_getKeyState(input, W, &in);
//     if (res == NOVELRT_SUCCESS) {
//         if (NovelRT_KeyStateFrameChangeLog_compareKeyState(KeyDown, in) == NOVELRT_TRUE) {
//             NovelRT_LoggingService_logInfoLine(console, "W was pressed!");
//             float vn = NovelRT_Timestamp_getSecondsFloat(delta);
//             //Need to find a way for variadic messages in NovelRT_LoggingService
//             fprintf(stdout, "Timestamp: %f \r\n", vn);
//         }
//     }
//     else {
//         char* errMsg = error;
//         NovelRT_LoggingService_logErrorLine(console, errMsg);
//     }
// }

// void timerTest(NovelRTTimestamp delta) {
//     uint32_t fps = 0;
//     res = NovelRT_StepTimer_getFramesPerSecond(timer, &fps);
//     NovelRT_Timestamp_getSecondsFloat(delta);
//     if (res == NOVELRT_SUCCESS) {
//         fprintf(stdout, "FPS: %f \n", (double)(fps));
//     }
// }

void renderNovelChan() {
    NovelRT_ImageRect_executeObjectBehaviour(nChanRect);
}

void appendFilePath(char* toAppend, char* destination) {
    char* dirMarker = "/";

#if defined(_WIN32) || defined(WIN32)
    dirMarker = "\\";
#endif

strcat(destination, dirMarker);
strcat(destination, toAppend);
} 

void moveNovelChan(NovelRTTimestamp delta) {
    if (nChanRect == NULL) return;
    
    int32_t bounced = 0;
    float trueDelta = 0.0f;
    float moveAmount = 100.0f;

    NovelRT_Timestamp_getSecondsFloat(delta, &trueDelta);
    NovelRTTransform transform = {{0, 0}, {0, 0}, 0};
    NovelRT_ImageRect_getTransform(nChanRect, &transform);
   

    float xOrigin = transform.position.x;
    float yOrigin = transform.position.y;

    float rectXSize = transform.scale.x;
    float rectQuarterSizeX = rectXSize / 4.0f;
    float rectYSize = transform.scale.y;
    float rectQuarterSizeY = rectYSize / 4.0f; 
    
    float xMax = 1920.0f;
    float xMin = 0.0f;
    float yMax = 1080.0f;
    float yMin = 0.0f;
    
    if (hMove == 1) {
        transform.position.x += (moveAmount * trueDelta);
        if (transform.position.x >= (xMax - rectQuarterSizeX)) {
            hMove = 0;
            bounced = 1;
            NovelRT_LoggingService_logInfoLine(console, "Flipped X axis movement.");
        } 
    } else {
        transform.position.x -= (moveAmount * trueDelta);
        if (transform.position.x <= (xMin + rectQuarterSizeX)) {
            hMove = 1;
            bounced = 1;
            NovelRT_LoggingService_logInfoLine(console, "Flipped X axis movement.");
        }
    }

    if (vMove == 1) {
        transform.position.y += (moveAmount * trueDelta);
        if (transform.position.y >= (yMax - rectQuarterSizeY)) {
            vMove = 0;
            bounced = 1;
            NovelRT_LoggingService_logInfoLine(console, "Flipped Y axis movement.");
        } 
    } else {
        transform.position.y -= (moveAmount * trueDelta);
        if (transform.position.y <= (yMin + rectQuarterSizeY)) {
            vMove = 1;
            bounced = 1;
            NovelRT_LoggingService_logInfoLine(console, "Flipped Y axis movement.");
        }
    }

    if (bounced == 1) {
        bounced = 0;
        NovelRT_RGBAConfig_setR(colourChange, (rand() % 256));
        NovelRT_RGBAConfig_setG(colourChange, (rand() % 256));
        NovelRT_RGBAConfig_setB(colourChange, (rand() % 256));
        NovelRT_ImageRect_setColourTint(nChanRect, colourChange);
    }

    NovelRT_ImageRect_setTransform(nChanRect, transform);
    
}


int main() {
    srand(time(NULL));
    NovelRTNovelRunner runner = NovelRT_NovelRunner_create(0);
    
    console = NovelRT_LoggingService_createCustomTitle("Interop");

    char* path = "";
    NovelRT_getExecutableDirPath(&path);
    appendFilePath("Resources", path);
    res = NovelRT_NovelRunner_getAudioService(runner, &audio);
    if (res == NOVELRT_FAILURE) {
        char* precursor = "Error getting AudioService: ";
        char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
        strcpy(errMsg, precursor);
        strcpy(errMsg, error);
        NovelRT_LoggingService_logErrorLine(console, errMsg);
        return -1;
    }
    else {
        res = NovelRT_LoggingService_throwIfNullPtr(console, &audio, "AudioService was not returned properly! Exiting...");
        res = NovelRT_AudioService_initialiseAudio(audio, &booleanResult);
        if (res == NOVELRT_SUCCESS) {
            NovelRT_LoggingService_logInfoLine(console, "Initialised Audio from C API!");
        }
        else {
            char* precursor = "Error initialising Audio: ";
            char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
            strcpy(errMsg, precursor);
            strcpy(errMsg, error);
            NovelRT_LoggingService_logErrorLine(console, errMsg);
        }   
    }

    res = NovelRT_NovelRunner_getInteractionService(runner, &input);
    if (res == NOVELRT_SUCCESS) {
        NovelRT_LoggingService_logInfoLine(console, "Received InteractionService from C!");
    }
    else {
       char* precursor = "Error getting InteractionService: ";
            char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
            strcpy(errMsg, precursor);
            strcpy(errMsg, error);
            NovelRT_LoggingService_logErrorLine(console, errMsg);
            return -1;
    }

    res = NovelRT_NovelRunner_getRuntimeService(runner, &dotnet);
    if (res == NOVELRT_SUCCESS) {
        NovelRT_LoggingService_logInfoLine(console, "Received .NET RuntimeService from C!");
    }
    else {
       char* precursor = "Error getting RuntimeService: ";
            char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
            strcpy(errMsg, precursor);
            strcpy(errMsg, error);
            NovelRT_LoggingService_logErrorLine(console, errMsg);
            return -1;
    }

    NovelRT_RuntimeService_initialise(dotnet);

    NovelRTRenderingService renderer = NULL;
    res = NovelRT_NovelRunner_getRenderer(runner, &renderer);
    colourChange = NovelRT_RGBAConfig_Create(0,0,0,255);

    NovelRTRGBAConfig background = NovelRT_RGBAConfig_Create(0,0,0,0);
    NovelRT_RenderingService_setBackgroundColour(renderer, background);

    NovelRTGeoVector2F nChanPosition = { 1920 / 2, 1080 / 2 };
    NovelRTGeoVector2F nChanSize = { 762, 881 };
    NovelRTTransform nChanTransform = { nChanPosition, nChanSize, 0 };
    NovelRTRGBAConfig nChanColours = NovelRT_RGBAConfig_Create(255, 255, 255, 255);

    char* nChanFileLocation = "";
    strcat(nChanFileLocation, path);
    appendFilePath("Images", nChanFileLocation);
    appendFilePath("novel-chan.png", nChanFileLocation);
    NovelRT_LoggingService_logInfoLine(console, nChanFileLocation);
    res = NovelRT_RenderingService_createImageRectWithFile(renderer, &nChanRect, nChanTransform, 3, nChanFileLocation, nChanColours);

    NovelRT_NovelRunner_addSceneConstructionRequested(runner, &renderNovelChan);

    NovelRT_NovelRunner_addUpdate(runner, moveNovelChan);

    NovelRT_NovelRunner_runNovel(runner);

    return 0;
}

