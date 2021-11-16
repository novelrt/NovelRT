// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#define NOVELRT_C_API 1
#include <NovelRT.h>
#include <NovelRT.Interop/Ecs/Audio/NrtEcsAudio.h>
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
int32_t playAudio = 0;
NrtAudioEmitterStateComponent toPlayState = { NRT_EMITTER_STATE_TOPLAY };

char flippedAxisTempBuffer[1024];

//ECS
NrtAudioSystemHandle audio = NULL;
NrtSystemSchedulerHandle scheduler = NULL;
NrtComponentCacheHandle componentCache = NULL;
NrtEntityCacheHandle entityCache = NULL;
NrtEntityId singleEntity = 0;
NrtComponentTypeId audioEmitterId = 0;
NrtComponentTypeId emitterStateId = 0;

    // Services
NrtInteractionServiceHandle input = NULL;
NrtLoggingServiceHandle console = NULL;
NrtStepTimerHandle timer = NULL;
NrtRenderingServiceHandle renderer = NULL;
NrtUtilitiesEventWithTimestampHandle updateEvent = NULL;
NrtRGBAColourHandle colourChange = NULL;

// Objects
NrtImageRectHandle nChanRect = NULL;
NrtBasicInteractionRectHandle interactRect = NULL;
uint32_t goatHandle = 0;

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
        playAudio = 1;
        bounced = 0;
        Nrt_RGBAColour_setR(colourChange, (rand() % 256));
        Nrt_RGBAColour_setG(colourChange, (rand() % 256));
        Nrt_RGBAColour_setB(colourChange, (rand() % 256));
        Nrt_ImageRect_setColourTint(nChanRect, colourChange);
    }

    Nrt_ImageRect_setTransform(nChanRect, transform);
    Nrt_Input_BasicInteractionRect_setTransform(interactRect, transform);
}

void UpdateAudio(NrtTimestamp delta, void* context)
{
    if (scheduler == NULL)
        return;

    if(playAudio == 1)
    {
        playAudio = 0;
        Nrt_AudioSystem_PushEmitterStateComponentUpdate(scheduler, singleEntity, toPlayState);
    }

    Nrt_SystemScheduler_ExecuteIteration(scheduler, delta);
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

    // Changing Background Colour
    res = Nrt_NovelRunner_getRenderer(runner, &renderer);
    if (res != NRT_SUCCESS)
    {
        const char* const textParts[2] = {"Error getting RenderingService: ", Nrt_getLastError()};
        const char* errMsg = Nrt_appendText(2, textParts);
        Nrt_LoggingService_logErrorLine(console, errMsg);
        return -1;
    }
    colourChange = Nrt_RGBAColour_Create(0, 0, 0, 255);

    NrtRGBAColourHandle background = Nrt_RGBAColour_Create(0, 0, 0, 0);
    Nrt_RenderingService_setBackgroundColour(renderer, background);

    // Creating ImageRect
    NrtGeoVector2F nChanPosition = {1920 / 2, 1080 / 2};
    NrtGeoVector2F nChanSize = {762, 881};
    NrtTransform nChanTransform = {nChanPosition, nChanSize, 0};
    NrtRGBAColourHandle nChanColours = Nrt_RGBAColour_Create(255, 255, 255, 255);

    {
        const char* const pathParts[3] = {path, "Images", "novel-chan.png"};
        const char* nChanFileLocation = Nrt_appendFilePath(3, pathParts);
        res = Nrt_RenderingService_createImageRectWithFile(renderer, &nChanRect, nChanTransform, 3, nChanFileLocation,
                                                           nChanColours);
    }

    // Creating InteractionRect
    NrtTransform interactTransform = {nChanPosition, nChanSize, 0};
    res = Nrt_InteractionService_createBasicInteractionRect(input, interactTransform, 3, &interactRect);

    //Setting up ECS & Audio
    scheduler = Nrt_SystemScheduler_Create(4);
    componentCache = Nrt_SystemScheduler_GetComponentCache(scheduler);
    entityCache = Nrt_SystemScheduler_GetEntityCache(scheduler);
    audio = Nrt_AudioSystem_Create();
    {
        const char* const audioPathParts[3] = {path, "Sounds", "goat.ogg"};
        const char* goatFileLocation = Nrt_appendFilePath(3, audioPathParts);
        res = Nrt_AudioSystem_CreateAudio(audio, goatFileLocation, NRT_FALSE, &goatHandle);
    }

    //Create the components
    NrtAudioEmitterComponent goat = { goatHandle, 0, 0, 1.0};
    NrtAudioEmitterComponent deleted = { -1, 0, 0, 0};
    NrtAudioEmitterStateComponent goatState = { NRT_EMITTER_STATE_STOPPED };
    NrtAudioEmitterStateComponent deletedState = { NRT_EMITTER_STATE_DONE };

    //Create the system's update function pointer
    NrtCatalogueHandle catalogue = Nrt_Catalogue_Create(0,componentCache, entityCache);
    void(*updateAudio)(NrtTimestamp, NrtCatalogueHandle, void*) = Nrt_AudioSystem_Update;
    NrtSystemUpdateFnPtr updateAudioPtr = updateAudio;

    //Create the entity
    singleEntity = Nrt_Catalogue_CreateEntity(catalogue);

    //Register the System & Component
    Nrt_SystemScheduler_RegisterSystem(scheduler, updateAudioPtr, audio);
    Nrt_AudioSystem_RegisterDefaultAudioComponents(scheduler);

    //Add the components
    Nrt_AudioSystem_PushEmitterComponentUpdate(scheduler, singleEntity, goat);
    Nrt_AudioSystem_PushEmitterStateComponentUpdate(scheduler, singleEntity, goatState);

    // Setting up Scene Construction
    Nrt_NovelRunner_SubscribeToSceneConstructionRequested(runner, &RenderNovelChan, NULL, NULL);

    // Setting up Update methods
    struct MoveContext moveContext = {0,0};
    Nrt_NovelRunner_SubscribeToUpdate(runner, MoveNovelChan, &moveContext, NULL);
    Nrt_NovelRunner_SubscribeToUpdate(runner, UpdateAudio, NULL, NULL);

    //Spin Threads
    Nrt_SystemScheduler_SpinThreads(scheduler);

    // Run the novel!
    Nrt_NovelRunner_runNovel(runner);

    return 0;
}
