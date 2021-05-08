// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#define NOVELRT_C_API 1
#include <NovelRT.h>

#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Preset vars
int32_t res = NRT_SUCCESS;
int32_t booleanResult = NRT_TRUE;
int32_t inkServiceProvided = NRT_FALSE;
int32_t hMove = 1; // 1 == move right, 0 == move left
int32_t vMove = 1; // 1 == move up, 0 == move down

char flippedAxisTempBuffer[1024];

// Services
NrtAudioServiceHandle audio = NULL;
NrtInteractionServiceHandle input = NULL;
NrtLoggingServiceHandle console = NULL;
NrtRuntimeServiceHandle dotnet = NULL;
NrtInkServiceHandle ink = NULL;
NrtStepTimerHandle timer = NULL;
NrtRenderingServiceHandle renderer = NULL;
NrtUtilitiesEventWithTimestampHandle updateEvent = NULL;
NrtRGBAConfigHandle colourChange = NULL;

// Objects
NrtImageRectHandle nChanRect = NULL;
NrtBasicInteractionRectHandle interactRect = NULL;
NrtStoryHandle story = NULL;

// Function to render NovelChan
void RenderNovelChan(void* context)
{
    Nrt_ImageRect_executeObjectBehaviour(nChanRect);
    Nrt_Input_BasicInteractionRect_executeObjectBehaviour(interactRect);
}

struct MoveContext
{
    int xBounces;
    int yBounces;
};

// Function to move NovelChan DVD screensaver style
void MoveNovelChan(NrtTimestamp delta, void* context)
{
    if (nChanRect == NULL)
        return;

    int32_t bounced = 0;
    float trueDelta = 0.0f;
    float moveAmount = 100.0f;
    struct MoveContext* moveContext = (struct MoveContext*)context;

    trueDelta = Nrt_Timestamp_getSecondsFloat(delta);
    NrtTransform transform = Nrt_ImageRect_getTransform(nChanRect);

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

    if (hMove == 1)
    {
        transform.position.x += (moveAmount * trueDelta);
        if (transform.position.x >= (xMax - rectQuarterSizeX))
        {
            hMove = 0;
            bounced = 1;
            int bounces = ++moveContext->xBounces;

            int size = snprintf(NULL, 0, "Flipped X axis movement. Count: %i", bounces);
            snprintf(flippedAxisTempBuffer, size + 1, "Flipped X axis movement. Count: %i", bounces);
            Nrt_LoggingService_logInfoLine(console, flippedAxisTempBuffer);
        }
    }
    else
    {
        transform.position.x -= (moveAmount * trueDelta);
        if (transform.position.x <= (xMin + rectQuarterSizeX))
        {
            hMove = 1;
            bounced = 1;
            int bounces = ++moveContext->xBounces;

            int size = snprintf(NULL, 0, "Flipped X axis movement. Count: %i", bounces);
            snprintf(flippedAxisTempBuffer, size + 1, "Flipped X axis movement. Count: %i", bounces);
            Nrt_LoggingService_logInfoLine(console, flippedAxisTempBuffer);
        }
    }

    if (vMove == 1)
    {
        transform.position.y += (moveAmount * trueDelta);
        if (transform.position.y >= (yMax - rectQuarterSizeY))
        {
            vMove = 0;
            bounced = 1;
            int bounces = ++moveContext->yBounces;

            int size = snprintf(NULL, 0, "Flipped Y axis movement. Count: %i", bounces);
            snprintf(flippedAxisTempBuffer, size + 1, "Flipped Y axis movement. Count: %i", bounces);
            Nrt_LoggingService_logInfoLine(console, flippedAxisTempBuffer);
        }
    }
    else
    {
        transform.position.y -= (moveAmount * trueDelta);
        if (transform.position.y <= (yMin + rectQuarterSizeY))
        {
            vMove = 1;
            bounced = 1;
            int bounces = ++moveContext->yBounces;

            int size = snprintf(NULL, 0, "Flipped Y axis movement. Count: %i", bounces);
            snprintf(flippedAxisTempBuffer, size + 1, "Flipped Y axis movement. Count: %i", bounces);
            Nrt_LoggingService_logInfoLine(console, flippedAxisTempBuffer);
        }
    }

    if (bounced == 1)
    {
        bounced = 0;
        Nrt_RGBAConfig_setR(colourChange, (rand() % 256));
        Nrt_RGBAConfig_setG(colourChange, (rand() % 256));
        Nrt_RGBAConfig_setB(colourChange, (rand() % 256));
        Nrt_ImageRect_setColourTint(nChanRect, colourChange);
    }

    Nrt_ImageRect_setTransform(nChanRect, transform);
    Nrt_Input_BasicInteractionRect_setTransform(interactRect, transform);
}

// Function to interact with Ink
void InteractWithNovelChan(void* context)
{
    if (Nrt_Story_canContinue(story) == NRT_FALSE)
    {
        Nrt_Story_resetState(story);
    }

    const char* cSharpResult = Nrt_Story_continue(story);
    Nrt_LoggingService_logDebugLine(console, cSharpResult);
    Nrt_RuntimeService_freeString(dotnet, cSharpResult);
}

int main()
{
    res = NRT_SUCCESS;
    srand(time(NULL));

    // Creating NovelRunner
    NrtNovelRunnerHandle runner = Nrt_NovelRunner_create(0);

    // Starting LoggingService
    console = Nrt_LoggingService_createCustomTitle("Interop");

    // Getting a constant to the Resources folder
    const char* execPath = Nrt_getExecutableDirPath();
    const char* error = Nrt_getLastError();
    if (error != NULL)
    {
        Nrt_LoggingService_logErrorLine(console, error);
        return -1;
    }

    const char* const pathParts[2] = {execPath, "Resources"};
    const char* path = Nrt_appendFilePath(2, pathParts);

    // Getting & Initialising AudioService
    res = Nrt_NovelRunner_getAudioService(runner, &audio);
    if (res != NRT_SUCCESS)
    {
        const char* const textParts[2] = {"Error getting AudioService: ", Nrt_getLastError()};
        const char* errMsg = Nrt_appendText(2, textParts);
        Nrt_LoggingService_logErrorLine(console, errMsg);
        return -1;
    }
    else
    {
        booleanResult = Nrt_AudioService_initialiseAudio(audio);
        if (booleanResult != NRT_TRUE)
        {
            const char* const textParts[2] = {"Error initialising AudioService: ", Nrt_getLastError()};
            const char* errMsg = Nrt_appendText(2, textParts);
            Nrt_LoggingService_logErrorLine(console, errMsg);
            return -1;
        }
    }

    // Getting InteractionService
    res = Nrt_NovelRunner_getInteractionService(runner, &input);
    if (res == NRT_SUCCESS)
    {
        Nrt_LoggingService_logInfoLine(console, "Received InteractionService from C!");
    }
    else
    {
        const char* const textParts[2] = {"Error getting InteractionService: ", Nrt_getLastError()};
        const char* errMsg = Nrt_appendText(2, textParts);
        Nrt_LoggingService_logErrorLine(console, errMsg);
        return -1;
    }

    // Getting & Initialising RuntimeService / InkService
    res = Nrt_NovelRunner_getRuntimeService(runner, &dotnet);
    if (res != NRT_SUCCESS)
    {
        const char* const textParts[2] = {"Error getting RuntimeService: ", Nrt_getLastError()};
        const char* errMsg = Nrt_appendText(2, textParts);
        Nrt_LoggingService_logErrorLine(console, errMsg);
        return -1;
    }
    else
    {
        Nrt_LoggingService_logInfoLine(console, "Received .NET RuntimeService from C API!");
        res = Nrt_RuntimeService_initialise(dotnet);
        if (res == NRT_SUCCESS)
        {
            if (Nrt_RuntimeService_getInkService(dotnet, &ink) == NRT_SUCCESS)
            {
                Nrt_LoggingService_logInfoLine(console, "Received Ink Service from C API!");
                inkServiceProvided = NRT_TRUE;
                Nrt_InkService_initialise(ink);
            }
            else
            {
                Nrt_LoggingService_logErrorLine(console, "Failed to receive Ink Service!");
            }
        }
    }

    // Changing Background Colour
    res = Nrt_NovelRunner_getRenderer(runner, &renderer);
    if (res != NRT_SUCCESS)
    {
        const char* const textParts[2] = {"Error getting RenderingService: ", Nrt_getLastError()};
        const char* errMsg = Nrt_appendText(2, textParts);
        Nrt_LoggingService_logErrorLine(console, errMsg);
        return -1;
    }
    colourChange = Nrt_RGBAConfig_Create(0, 0, 0, 255);

    NrtRGBAConfigHandle background = Nrt_RGBAConfig_Create(0, 0, 0, 0);
    Nrt_RenderingService_setBackgroundColour(renderer, background);

    // Creating ImageRect
    NrtGeoVector2F nChanPosition = {1920 / 2, 1080 / 2};
    NrtGeoVector2F nChanSize = {762, 881};
    NrtTransform nChanTransform = {nChanPosition, nChanSize, 0};
    NrtRGBAConfigHandle nChanColours = Nrt_RGBAConfig_Create(255, 255, 255, 255);

    {
        const char* const pathParts[3] = {path, "Images", "novel-chan.png"};
        const char* nChanFileLocation = Nrt_appendFilePath(3, pathParts);
        res = Nrt_RenderingService_createImageRectWithFile(renderer, &nChanRect, nChanTransform, 3, nChanFileLocation,
                                                           nChanColours);
    }

    // Creating InteractionRect
    NrtTransform interactTransform = {nChanPosition, nChanSize, 0};
    res = Nrt_InteractionService_createBasicInteractionRect(input, interactTransform, 3, &interactRect);

    // Creating Ink Story
    if (inkServiceProvided == NRT_TRUE)
    {
        const char* const pathParts[3] = {path, "Scripts", "story.json"};
        const char* storyLocation = Nrt_appendFilePath(3, pathParts);
        Nrt_LoggingService_logInfoLine(console, storyLocation);

        FILE* json = fopen(storyLocation, "rb");
        char* buffer = 0;
        long length;
        if (json != NULL)
        {
            fseek(json, 0, SEEK_END);
            length = ftell(json);
            fseek(json, 0, SEEK_SET);
            buffer = malloc(length + 1);
            if (buffer)
            {
                fread(buffer, 1, length, json);
            }
            fclose(json);
            buffer[length] = 0;
        }

        if (Nrt_InkService_createStory(ink, buffer, &story) == NRT_SUCCESS)
        {
            Nrt_Story_resetState(story);
        }
        Nrt_Input_BasicInteractionRect_addInteraction(interactRect, &InteractWithNovelChan, NULL);
    }

    // Setting up Scene Construction
    Nrt_NovelRunner_addSceneConstructionRequested(runner, &RenderNovelChan, NULL);

    // Setting up Update methods
    struct MoveContext moveContext;
    Nrt_NovelRunner_addUpdate(runner, MoveNovelChan, &moveContext);

    // Run the novel!
    Nrt_NovelRunner_runNovel(runner);

    return 0;
}
