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
int32_t res = NRT_SUCCESS;
int32_t booleanResult = NRT_TRUE;
int32_t hMove = 1;      // 1 == move right, 0 == move left
int32_t vMove = 1;      // 1 == move up, 0 == move down
NrtAudioService audio = NULL;
NrtInteractionService input = NULL;
NrtLoggingService console = NULL;
NrtRuntimeService dotnet = NULL;
NrtStepTimer timer = NULL;
NrtUtilitiesEventWithTimestamp updateEvent = NULL;
NrtRGBAConfig colourChange = NULL;

NrtImageRect nChanRect = NULL;

// void inputTest(NrtTimestamp delta) {    
//     NrtKeyStateFrameChangeLog in = NULL;
//     res = Nrt_InteractionService_getKeyState(input, W, &in);
//     if (res == NRT_SUCCESS) {
//         if (Nrt_KeyStateFrameChangeLog_compareKeyState(KeyDown, in) == NRT_TRUE) {
//             Nrt_LoggingService_logInfoLine(console, "W was pressed!");
//             float vn = Nrt_Timestamp_getSecondsFloat(delta);
//             //Need to find a way for variadic messages in Nrt_LoggingService
//             fprintf(stdout, "Timestamp: %f \r\n", vn);
//         }
//     }
//     else {
//         char* errMsg = error;
//         Nrt_LoggingService_logErrorLine(console, errMsg);
//     }
// }

// void timerTest(NrtTimestamp delta) {
//     uint32_t fps = 0;
//     res = Nrt_StepTimer_getFramesPerSecond(timer, &fps);
//     Nrt_Timestamp_getSecondsFloat(delta);
//     if (res == NRT_SUCCESS) {
//         fprintf(stdout, "FPS: %f \n", (double)(fps));
//     }
// }

void renderNovelChan() {
    Nrt_ImageRect_executeObjectBehaviour(nChanRect);
}

void appendFilePath(char* toAppend, char* destination) {
    char* dirMarker = "/";

#if defined(_WIN32) || defined(WIN32)
    dirMarker = "\\";
#endif

strcat(destination, dirMarker);
strcat(destination, toAppend);
} 

void moveNovelChan(NrtTimestamp delta) {
    if (nChanRect == NULL) return;
    
    int32_t bounced = 0;
    float trueDelta = 0.0f;
    float moveAmount = 100.0f;

    Nrt_Timestamp_getSecondsFloat(delta, &trueDelta);
    NrtTransform transform = {{0, 0}, {0, 0}, 0};
    Nrt_ImageRect_getTransform(nChanRect, &transform);
   

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
            Nrt_LoggingService_logInfoLine(console, "Flipped X axis movement.");
        } 
    } else {
        transform.position.x -= (moveAmount * trueDelta);
        if (transform.position.x <= (xMin + rectQuarterSizeX)) {
            hMove = 1;
            bounced = 1;
            Nrt_LoggingService_logInfoLine(console, "Flipped X axis movement.");
        }
    }

    if (vMove == 1) {
        transform.position.y += (moveAmount * trueDelta);
        if (transform.position.y >= (yMax - rectQuarterSizeY)) {
            vMove = 0;
            bounced = 1;
            Nrt_LoggingService_logInfoLine(console, "Flipped Y axis movement.");
        } 
    } else {
        transform.position.y -= (moveAmount * trueDelta);
        if (transform.position.y <= (yMin + rectQuarterSizeY)) {
            vMove = 1;
            bounced = 1;
            Nrt_LoggingService_logInfoLine(console, "Flipped Y axis movement.");
        }
    }

    if (bounced == 1) {
        bounced = 0;
        Nrt_RGBAConfig_setR(colourChange, (rand() % 256));
        Nrt_RGBAConfig_setG(colourChange, (rand() % 256));
        Nrt_RGBAConfig_setB(colourChange, (rand() % 256));
        Nrt_ImageRect_setColourTint(nChanRect, colourChange);
    }

    Nrt_ImageRect_setTransform(nChanRect, transform);
    
}


int main() {
    srand(time(NULL));
    NrtNovelRunner runner = Nrt_NovelRunner_create(0);
    
    console = Nrt_LoggingService_createCustomTitle("Interop");

    char* path = "";
    Nrt_getExecutableDirPath(&path);
    appendFilePath("Resources", path);
    res = Nrt_NovelRunner_getAudioService(runner, &audio);
    if (res == NRT_FAILURE_UNKOWN) {
        char* precursor = "Error getting AudioService: ";
        char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
        strcpy(errMsg, precursor);
        strcpy(errMsg, error);
        Nrt_LoggingService_logErrorLine(console, errMsg);
        return -1;
    }
    else {
        res = Nrt_LoggingService_throwIfNullPtr(console, &audio, "AudioService was not returned properly! Exiting...");
        res = Nrt_AudioService_initialiseAudio(audio, &booleanResult);
        if (res == NRT_SUCCESS) {
            Nrt_LoggingService_logInfoLine(console, "Initialised Audio from C API!");
        }
        else {
            char* precursor = "Error initialising Audio: ";
            char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
            strcpy(errMsg, precursor);
            strcpy(errMsg, error);
            Nrt_LoggingService_logErrorLine(console, errMsg);
        }   
    }

    res = Nrt_NovelRunner_getInteractionService(runner, &input);
    if (res == NRT_SUCCESS) {
        Nrt_LoggingService_logInfoLine(console, "Received InteractionService from C!");
    }
    else {
       char* precursor = "Error getting InteractionService: ";
            char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
            strcpy(errMsg, precursor);
            strcpy(errMsg, error);
            Nrt_LoggingService_logErrorLine(console, errMsg);
            return -1;
    }

    res = Nrt_NovelRunner_getRuntimeService(runner, &dotnet);
    if (res == NRT_SUCCESS) {
        Nrt_LoggingService_logInfoLine(console, "Received .NET RuntimeService from C!");
    }
    else {
       char* precursor = "Error getting RuntimeService: ";
            char* errMsg = (char*)malloc(1+strlen(precursor)+strlen(error));
            strcpy(errMsg, precursor);
            strcpy(errMsg, error);
            Nrt_LoggingService_logErrorLine(console, errMsg);
            return -1;
    }

    Nrt_RuntimeService_initialise(dotnet);

    NrtRenderingService renderer = NULL;
    res = Nrt_NovelRunner_getRenderer(runner, &renderer);
    colourChange = Nrt_RGBAConfig_Create(0,0,0,255);

    NrtRGBAConfig background = Nrt_RGBAConfig_Create(0,0,0,0);
    Nrt_RenderingService_setBackgroundColour(renderer, background);

    NrtGeoVector2F nChanPosition = { 1920 / 2, 1080 / 2 };
    NrtGeoVector2F nChanSize = { 762, 881 };
    NrtTransform nChanTransform = { nChanPosition, nChanSize, 0 };
    NrtRGBAConfig nChanColours = Nrt_RGBAConfig_Create(255, 255, 255, 255);

    char* nChanFileLocation = "";
    strcat(nChanFileLocation, path);
    appendFilePath("Images", nChanFileLocation);
    appendFilePath("novel-chan.png", nChanFileLocation);
    Nrt_LoggingService_logInfoLine(console, nChanFileLocation);
    res = Nrt_RenderingService_createImageRectWithFile(renderer, &nChanRect, nChanTransform, 3, nChanFileLocation, nChanColours);

    Nrt_NovelRunner_addSceneConstructionRequested(runner, &renderNovelChan);

    Nrt_NovelRunner_addUpdate(runner, moveNovelChan);

    Nrt_NovelRunner_runNovel(runner);

    return 0;
}

