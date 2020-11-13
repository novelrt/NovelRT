#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/NrtNovelRunner.h"
#include "NovelRT.Interop/Input/NrtInteractionService.h"
#include "NovelRT.Interop/Timing/NrtTimestamp.h"
#include "NovelRT.Interop/Timing/NrtStepTimer.h"
#include "NovelRT.Interop/Utilities/NrtCommonEvents.h"
#include "NovelRT.Interop/NrtLoggingService.h"
#include "NovelRT.Interop/Graphics/NrtGraphicsTypedefs.h"
#include "NovelRT.Interop/Utilities/NrtMisc.h"
#include "NovelRT.Interop/Graphics/NrtImageRect.h"
#include "NovelRT.Interop/Ink/NrtInkService.h"
#include "NovelRT.Interop/Ink/NrtStory.h"

const char* error = " ";
int32_t res = NRT_SUCCESS;
int32_t booleanResult = NRT_TRUE;
int32_t inkServiceProvided = NRT_FALSE;
int32_t hMove = 1;      // 1 == move right, 0 == move left
int32_t vMove = 1;      // 1 == move up, 0 == move down
NrtAudioService audio = NULL;
NrtInteractionService input = NULL;
NrtLoggingService console = NULL;
NrtRuntimeService dotnet = NULL;
NrtInkService ink = NULL;
NrtStepTimer timer = NULL;
NrtUtilitiesEventWithTimestamp updateEvent = NULL;
NrtRGBAConfig colourChange = NULL;

NrtImageRect nChanRect = NULL;
NrtBasicInteractionRect interactRect = NULL;
NrtStory story = NULL;

//Function to render NovelChan
void renderNovelChan() {
    Nrt_ImageRect_executeObjectBehaviour(nChanRect);
    Nrt_Input_BasicInteractionRect_executeObjectBehaviour(interactRect);
}

//Filesystem string helper
void appendFilePath(char* toAppend, char* destination) {
    char* dirMarker = "/";

#if defined(_WIN32) || defined(WIN32)
    dirMarker = "\\";
#endif

strcat(destination, dirMarker);
strcat(destination, toAppend);
}

//Function to move NovelChan DVD screensaver style
void moveNovelChan(NrtTimestamp delta) {
    if (nChanRect == NULL) return;

    int32_t bounced = 0;
    float trueDelta = 0.0f;
    float moveAmount = 100.0f;

    trueDelta = Nrt_Timestamp_getSecondsFloat(delta);
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
    Nrt_Input_BasicInteractionRect_setTransform(interactRect, transform);
}

//Function to interact with Ink
void interactWithNovelChan() {
  if(Nrt_Story_canContinue(story) == NRT_FALSE) {
    Nrt_Story_resetState(story);
  }

  const char* cSharpResult = "";
  Nrt_Story_continue(story, &cSharpResult);
  Nrt_LoggingService_logDebugLine(console, cSharpResult);
  Nrt_RuntimeService_freeString(dotnet, cSharpResult);
}

int main() {
    srand(time(NULL));
    NrtNovelRunner runner = Nrt_NovelRunner_create(0);

    console = Nrt_LoggingService_createCustomTitle("Interop");

    char* path = "";
    Nrt_getExecutableDirPath(&path);
    appendFilePath("Resources", path);
    res = Nrt_NovelRunner_getAudioService(runner, &audio);
    if (res != NRT_SUCCESS) {
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
    if(Nrt_RuntimeService_getInkService(dotnet, &ink) == NRT_SUCCESS) {
      Nrt_LoggingService_logInfoLine(console, "Received Ink Service from C API!");
      inkServiceProvided = NRT_TRUE;
      Nrt_InkService_initialise(ink);
    }
    else {
      Nrt_LoggingService_logErrorLine(console, "Failed to receive Ink Service!");
    }

    //Changing Background Colour
    NrtRenderingService renderer = NULL;
    res = Nrt_NovelRunner_getRenderer(runner, &renderer);
    colourChange = Nrt_RGBAConfig_Create(0,0,0,255);

    NrtRGBAConfig background = Nrt_RGBAConfig_Create(0,0,0,0);
    Nrt_RenderingService_setBackgroundColour(renderer, background);

    //Creating ImageRect
    NrtGeoVector2F nChanPosition = { 1920 / 2, 1080 / 2 };
    NrtGeoVector2F nChanSize = { 762, 881 };
    NrtTransform nChanTransform = { nChanPosition, nChanSize, 0 };
    NrtRGBAConfig nChanColours = Nrt_RGBAConfig_Create(255, 255, 255, 255);

    char* nChanFileLocation = "";
    strcat(nChanFileLocation, path);
    appendFilePath("Images", nChanFileLocation);
    appendFilePath("novel-chan.png", nChanFileLocation);
    res = Nrt_RenderingService_createImageRectWithFile(renderer, &nChanRect, nChanTransform, 3, nChanFileLocation, nChanColours);

    //Creating InteractionRect
    NrtTransform interactTransform = { nChanPosition, nChanSize, 0 };
    res = Nrt_InteractionService_createBasicInteractionRect(input, interactTransform,3, &interactRect);

    //Creating Ink Story
    if (inkServiceProvided == NRT_TRUE) {
      char* storyLocation = NULL;
      char* scriptPath = "";
      Nrt_getExecutableDirPath(&scriptPath);
      appendFilePath("Resources", scriptPath);
      storyLocation = (char*)malloc(sizeof(scriptPath) + 1);
      strcpy(storyLocation, scriptPath);
      appendFilePath("Scripts", storyLocation);
      appendFilePath("story.json", storyLocation);
      Nrt_LoggingService_logInfoLine(console, storyLocation);

      FILE* json = fopen(storyLocation, "rb");
      char* buffer = 0;
      long length;
      if (json != NULL) {
        fseek(json, 0, SEEK_END);
        length = ftell(json);
        fseek(json, 0, SEEK_SET);
        buffer = malloc(length + 1);
        if(buffer) {
          fread(buffer, 1, length, json);
        }
        fclose(json);
        buffer[length] = 0;
      }

      if(Nrt_InkService_createStory(ink, buffer, &story) == NRT_SUCCESS) {
        Nrt_Story_resetState(story);
      }

      Nrt_Input_BasicInteractionRect_addInteraction(interactRect, &interactWithNovelChan);
    }

    //Setting up rendering
    Nrt_NovelRunner_addSceneConstructionRequested(runner, &renderNovelChan);

    //Setting up Update methods
    Nrt_NovelRunner_addUpdate(runner, moveNovelChan);

    //Run the novel!
    Nrt_NovelRunner_runNovel(runner);

    return 0;
}

