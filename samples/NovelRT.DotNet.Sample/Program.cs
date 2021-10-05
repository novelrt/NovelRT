// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using NovelRT.Interop;
using static System.Net.Mime.MediaTypeNames;
using static NovelRT.Interop.NovelRT;
using static NovelRT.Interop.NrtBool;
using static NovelRT.Interop.NrtResult;

namespace NovelRT.DotNet.Sample
{
    public static unsafe class Program
    {
        private static NrtResult res = NRT_SUCCESS;
        private static NrtBool booleanResult = NRT_TRUE;
        private static NrtBool inkServiceProvided = NRT_FALSE;

        private static int hMove = 1; // 1 == move right, 0 == move left
        private static int vMove = 1; // 1 == move up, 0 == move down

        // Services
        private static IntPtr audio = IntPtr.Zero;
        private static IntPtr input = IntPtr.Zero;
        private static IntPtr console = IntPtr.Zero;
        private static IntPtr dotnet = IntPtr.Zero;
        private static IntPtr ink = IntPtr.Zero;
        private static IntPtr timer = IntPtr.Zero;
        private static IntPtr renderer = IntPtr.Zero;
        private static IntPtr updateEvent = IntPtr.Zero;
        private static IntPtr colourChange = IntPtr.Zero;

        // Objects
        private static IntPtr nChanRect = IntPtr.Zero;
        private static IntPtr interactRect = IntPtr.Zero;
        private static IntPtr story = IntPtr.Zero;

        private static Random rand = null;

        public static int Main(string[] args)
        {
            res = NRT_SUCCESS;
            rand = new Random();

            // Creating NovelRunner
            IntPtr runner = Nrt_NovelRunner_create(0);

            // Starting LoggingService
            fixed (byte* customTitle = Encoding.UTF8.GetBytes("Interop"))
            {
                console = Nrt_LoggingService_createCustomTitle((sbyte*)customTitle);
            }

            // Getting a constant to the Resources folder
            sbyte* execPath = Nrt_getExecutableDirPath();
            sbyte* error = Nrt_getLastError();

            if (error != null)
            {
                Nrt_LoggingService_logErrorLine(console, error);
                return -1;
            }

            sbyte* path;

            fixed (byte* pathPart = Encoding.UTF8.GetBytes("Resources"))
            {
                var pathParts = stackalloc sbyte*[2] { execPath, (sbyte*)pathPart };
                path = Nrt_appendFilePath(2, pathParts);
            }

            // Getting & Initialising AudioService
            fixed (IntPtr* pAudio = &audio)
            {
                res = (NrtResult)Nrt_NovelRunner_getAudioService(runner, pAudio);
            }

            if (res != NRT_SUCCESS)
            {
                fixed (byte* text = Encoding.UTF8.GetBytes("Error getting AudioService: "))
                {
                    var textParts = stackalloc sbyte*[2] { (sbyte*)text, Nrt_getLastError() };
                    sbyte* errMsg = Nrt_appendText(2, textParts);
                    Nrt_LoggingService_logErrorLine(console, errMsg);
                }
                return -1;
            }
            else
            {
                booleanResult = (NrtBool)Nrt_AudioService_initialiseAudio(audio);

                if (booleanResult != NRT_TRUE)
                {
                    fixed (byte* text = Encoding.UTF8.GetBytes("Error initialising AudioService: "))
                    {
                        var textParts = stackalloc sbyte*[2] { (sbyte*)text, Nrt_getLastError() };
                        sbyte* errMsg = Nrt_appendText(2, textParts);
                        Nrt_LoggingService_logErrorLine(console, errMsg);
                    }
                    return -1;
                }
            }

            // Getting InteractionService
            fixed (IntPtr* pInput = &input)
            {
                res = (NrtResult)Nrt_NovelRunner_getInteractionService(runner, pInput);
            }

            if (res == NRT_SUCCESS)
            {
                fixed (byte* info = Encoding.UTF8.GetBytes("Received InteractionService from C via C#!"))
                {
                    Nrt_LoggingService_logInfoLine(console, (sbyte*)info);
                }
            }
            else
            {
                fixed (byte* text = Encoding.UTF8.GetBytes("Error getting InteractionService: "))
                {
                    var textParts = stackalloc sbyte*[2] { (sbyte*)text, Nrt_getLastError() };
                    sbyte* errMsg = Nrt_appendText(2, textParts);
                    Nrt_LoggingService_logErrorLine(console, errMsg);
                }
                return -1;
            }

            // Getting & Initialising RuntimeService / InkService
            fixed (IntPtr* pDotnet = &dotnet)
            {
                res = (NrtResult)Nrt_NovelRunner_getRuntimeService(runner, pDotnet);
            }

            if (res != NRT_SUCCESS)
            {
                fixed (byte* text = Encoding.UTF8.GetBytes("Error getting RuntimeService: "))
                {
                    var textParts = stackalloc sbyte*[2] { (sbyte*)text, Nrt_getLastError() };
                    sbyte* errMsg = Nrt_appendText(2, textParts);
                    Nrt_LoggingService_logErrorLine(console, errMsg);
                }
                return -1;
            }
            else
            {
                fixed (byte* info = Encoding.UTF8.GetBytes("Received .NET RuntimeService from C API via C#!"))
                {
                    Nrt_LoggingService_logInfoLine(console, (sbyte*)info);
                }
                res = (NrtResult)Nrt_RuntimeService_initialise(dotnet);

                if (res == NRT_SUCCESS)
                {
                    fixed (IntPtr* pInk = &ink)
                    {
                        res = (NrtResult)Nrt_RuntimeService_getInkService(dotnet, pInk);
                    }

                    if (res == NRT_SUCCESS)
                    {
                        fixed (byte* info = Encoding.UTF8.GetBytes("Received Ink Service from C API via C#!"))
                        {
                            Nrt_LoggingService_logInfoLine(console, (sbyte*)info);
                        }
                        inkServiceProvided = NRT_TRUE;
                        Nrt_InkService_initialise(ink);
                    }
                    else
                    {
                        fixed (byte* info = Encoding.UTF8.GetBytes("Failed to receive Ink Service!"))
                        {
                            Nrt_LoggingService_logErrorLine(console, (sbyte*)info);
                        }
                    }
                }
            }

            // Changing Background Colour
            fixed (IntPtr* pRenderer = &renderer)
            {
                res = (NrtResult)Nrt_NovelRunner_getRenderer(runner, pRenderer);
            }

            if (res != NRT_SUCCESS)
            {
                fixed (byte* text = Encoding.UTF8.GetBytes("Error getting RenderingService: "))
                {
                    var textParts = stackalloc sbyte*[2] { (sbyte*)text, Nrt_getLastError() };
                    sbyte* errMsg = Nrt_appendText(2, textParts);
                    Nrt_LoggingService_logErrorLine(console, errMsg);
                }
                return -1;
            }

            colourChange = Nrt_RGBAColour_Create(0, 0, 0, 255);

            IntPtr background = Nrt_RGBAColour_Create(0, 0, 0, 0);
            Nrt_RenderingService_setBackgroundColour(renderer, background);

            // Creating ImageRect
            NrtGeoVector2F nChanPosition = new NrtGeoVector2F { x = 1920 / 2, y = 1080 / 2 };
            NrtGeoVector2F nChanSize = new NrtGeoVector2F { x = 762, y = 881 };
            NrtTransform nChanTransform = new NrtTransform { position = nChanPosition, scale = nChanSize, rotation = 0 };
            IntPtr nChanColours = Nrt_RGBAColour_Create(255, 255, 255, 255);

            sbyte* nChanFileLocation;

            fixed (byte* filePathPart1 = Encoding.UTF8.GetBytes("Images"))
            fixed (byte* filePathPart2 = Encoding.UTF8.GetBytes("novel-chan.png"))
{
                var pathParts = stackalloc sbyte*[3] { path, (sbyte*)filePathPart1, (sbyte*)filePathPart2 };
                nChanFileLocation = Nrt_appendFilePath(3, pathParts);
            }

            fixed (IntPtr* pNChanRect = &nChanRect)
            {
                res = (NrtResult)Nrt_RenderingService_createImageRectWithFile(renderer, pNChanRect, nChanTransform, 3, nChanFileLocation, nChanColours);
            }

            // Creating InteractionRect
            NrtTransform interactTransform = new NrtTransform { position = nChanPosition, scale = nChanSize, rotation = 0 };

            fixed (IntPtr* pInteractRect = &interactRect)
            {
                res = (NrtResult)Nrt_InteractionService_createBasicInteractionRect(input, interactTransform, 3, pInteractRect);
            }

            // Creating Ink Story
            if (inkServiceProvided == NRT_TRUE)
            {
                sbyte* storyLocation;

                fixed (byte* filePathPart1 = Encoding.UTF8.GetBytes("Scripts"))
                fixed (byte* filePathPart2 = Encoding.UTF8.GetBytes("story.json"))
                {
                    var pathParts = stackalloc sbyte*[3] { path, (sbyte*)filePathPart1, (sbyte*)filePathPart2 };
                    storyLocation = Nrt_appendFilePath(3, pathParts);
                }

                Nrt_LoggingService_logInfoLine(console, storyLocation);
                string buffer = File.ReadAllText(Marshal.PtrToStringAnsi((IntPtr)storyLocation));

                fixed (IntPtr* pStory = &story)
                fixed (byte* pBuffer = Encoding.UTF8.GetBytes(buffer))
                {
                    res = (NrtResult)Nrt_InkService_createStory(ink, (sbyte*)pBuffer, pStory);
                }

                if (res == NRT_SUCCESS)
                {
                    Nrt_Story_resetState(story);
                }
                Nrt_Input_BasicInteractionRect_addInteraction(interactRect, &interactWithNovelChan, null);
            }

            // Setting up Scene Construction
            Nrt_NovelRunner_SubscribeToSceneConstructionRequested(runner, &renderNovelChan, null, null);

            // Setting up Update methods
            Nrt_NovelRunner_SubscribeToUpdate(runner, &moveNovelChan, null, null);

            // Run the novel!
            Nrt_NovelRunner_runNovel(runner);

            return 0;
        }

        // Function to render NovelChan
        [UnmanagedCallersOnly]
        private static unsafe void renderNovelChan(void* contextData)
        {
            Nrt_ImageRect_executeObjectBehaviour(nChanRect);
            Nrt_Input_BasicInteractionRect_executeObjectBehaviour(interactRect);
        }

        // Function to move NovelChan DVD screensaver style
        [UnmanagedCallersOnly]
        private static unsafe void moveNovelChan(ulong delta, void* contextData)
        {
            if (nChanRect == IntPtr.Zero)
                return;

            int bounced = 0;
            float trueDelta = 0.0f;
            float moveAmount = 100.0f;

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

                    fixed (byte* info = Encoding.UTF8.GetBytes("Flipped X axis movement."))
                    {
                        Nrt_LoggingService_logInfoLine(console, (sbyte*)info);
                    }
                }
            }
            else
            {
                transform.position.x -= (moveAmount * trueDelta);
                if (transform.position.x <= (xMin + rectQuarterSizeX))
                {
                    hMove = 1;
                    bounced = 1;

                    fixed (byte* info = Encoding.UTF8.GetBytes("Flipped X axis movement."))
                    {
                        Nrt_LoggingService_logInfoLine(console, (sbyte*)info);
                    }
                }
            }

            if (vMove == 1)
            {
                transform.position.y += (moveAmount * trueDelta);
                if (transform.position.y >= (yMax - rectQuarterSizeY))
                {
                    vMove = 0;
                    bounced = 1;

                    fixed (byte* info = Encoding.UTF8.GetBytes("Flipped Y axis movement."))
                    {
                        Nrt_LoggingService_logInfoLine(console, (sbyte*)info);
                    }
                }
            }
            else
            {
                transform.position.y -= (moveAmount * trueDelta);
                if (transform.position.y <= (yMin + rectQuarterSizeY))
                {
                    vMove = 1;
                    bounced = 1;

                    fixed (byte* info = Encoding.UTF8.GetBytes("Flipped Y axis movement."))
                    {
                        Nrt_LoggingService_logInfoLine(console, (sbyte*)info);
                    }
                }
            }

            if (bounced == 1)
            {
                bounced = 0;
                Nrt_RGBAColour_setR(colourChange, (rand.Next() % 256));
                Nrt_RGBAColour_setG(colourChange, (rand.Next() % 256));
                Nrt_RGBAColour_setB(colourChange, (rand.Next() % 256));
                Nrt_ImageRect_setColourTint(nChanRect, colourChange);
            }

            Nrt_ImageRect_setTransform(nChanRect, transform);
            Nrt_Input_BasicInteractionRect_setTransform(interactRect, transform);
        }

        // Function to interact with Ink
        [UnmanagedCallersOnly]
        private static unsafe void interactWithNovelChan(void* contextData)
        {
            if ((NrtBool)Nrt_Story_canContinue(story) == NRT_FALSE)
            {
                Nrt_Story_resetState(story);
            }

            sbyte* cSharpResult = Nrt_Story_continue(story);
            Nrt_LoggingService_logDebugLine(console, cSharpResult);
            Nrt_RuntimeService_freeString(dotnet, cSharpResult);
        }
    }
}
