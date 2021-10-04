// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtTransform Nrt_BasicFillRect_getTransform([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_BasicFillRect_setTransform([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect, NrtTransform inputTransform);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_BasicFillRect_getLayer([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_BasicFillRect_setLayer([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect, [NativeTypeName("int32_t")] int inputLayer);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_BasicFillRect_getActive([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_BasicFillRect_setActive([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect, NrtBool inputBool);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_BasicFillRect_executeObjectBehaviour([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_BasicFillRect_getColourConfig([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect, [NativeTypeName("NrtRGBAColourHandle *")] IntPtr* outputColourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_BasicFillRect_setColourConfig([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect, [NativeTypeName("NrtRGBAColourHandle")] IntPtr inputColourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_BasicFillRect_getAsRenderObjectPtr([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect, [NativeTypeName("NrtRenderObjectHandle *")] IntPtr* outputRenderObject);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_BasicFillRect_destroy([NativeTypeName("NrtBasicFillRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtCameraHandle")]
        public static extern IntPtr Nrt_Camera_create();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_Camera_getViewMatrix([NativeTypeName("NrtCameraHandle")] IntPtr camera);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Camera_setViewMatrix([NativeTypeName("NrtCameraHandle")] IntPtr camera, NrtGeoMatrix4x4F inputMatrix);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_Camera_getProjectionMatrix([NativeTypeName("NrtCameraHandle")] IntPtr camera);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Camera_setProjectionMatrix([NativeTypeName("NrtCameraHandle")] IntPtr camera, NrtGeoMatrix4x4F inputMatrix);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_Camera_getCameraUboMatrix([NativeTypeName("NrtCameraHandle")] IntPtr camera);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtCameraFrameState Nrt_Camera_getFrameState([NativeTypeName("NrtCameraHandle")] IntPtr camera);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Camera_setForceResizeCallback([NativeTypeName("NrtCameraHandle")] IntPtr camera, [NativeTypeName("void (*)(NrtCameraHandle, NrtGeoVector2F, void *)")] delegate* unmanaged<IntPtr, NrtGeoVector2F, void*, void> callback, void* context);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtCameraHandle")]
        public static extern IntPtr Nrt_Camera_createDefaultOrthographicProjection(NrtGeoVector2F windowSize);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtCameraHandle")]
        public static extern IntPtr Nrt_Camera_createDefaultPerspectiveProjection(NrtGeoVector2F windowSize);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Camera_destroy([NativeTypeName("NrtCameraHandle")] IntPtr camera);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_FontSet_loadFontAsTextureSet([NativeTypeName("NrtFontSetHandle")] IntPtr fontSet, [NativeTypeName("const char *")] sbyte* file, float fontSize);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_FontSet_getFontFile([NativeTypeName("NrtFontSetHandle")] IntPtr fontSet, [NativeTypeName("const char **")] sbyte** outputFontFile);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_FontSet_getFontSize([NativeTypeName("NrtFontSetHandle")] IntPtr fontSet, float* outputFontSize);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtTransform Nrt_ImageRect_getTransform([NativeTypeName("NrtImageRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_setTransform([NativeTypeName("NrtImageRectHandle")] IntPtr rect, NrtTransform inputTransform);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_ImageRect_getLayer([NativeTypeName("NrtImageRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_setLayer([NativeTypeName("NrtImageRectHandle")] IntPtr rect, [NativeTypeName("int32_t")] int inputLayer);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_ImageRect_getActive([NativeTypeName("NrtImageRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_setActive([NativeTypeName("NrtImageRectHandle")] IntPtr rect, NrtBool inputBool);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_executeObjectBehaviour([NativeTypeName("NrtImageRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_getTexture([NativeTypeName("NrtImageRectHandle")] IntPtr rect, [NativeTypeName("NrtTextureHandle *")] IntPtr* outputTexture);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_setTexture([NativeTypeName("NrtImageRectHandle")] IntPtr rect, [NativeTypeName("NrtTextureHandle")] IntPtr inputTexture);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_getColourTint([NativeTypeName("NrtImageRectHandle")] IntPtr rect, [NativeTypeName("NrtRGBAColourHandle *")] IntPtr* outputColourTint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_setColourTint([NativeTypeName("NrtImageRectHandle")] IntPtr rect, [NativeTypeName("NrtRGBAColourHandle")] IntPtr inputColourTint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_getAsRenderObjectPtr([NativeTypeName("NrtImageRectHandle")] IntPtr rect, [NativeTypeName("NrtRenderObjectHandle *")] IntPtr* outputRenderObject);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ImageRect_destroy([NativeTypeName("NrtImageRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_create([NativeTypeName("NrtWindowingServiceHandle")] IntPtr windowingService, [NativeTypeName("NrtRenderingServiceHandle *")] IntPtr* outputRenderingService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_initialiseRendering([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_tearDown([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_createImageRectWithFile([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtImageRectHandle *")] IntPtr* outputImageRect, NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("const char *")] sbyte* filePath, [NativeTypeName("NrtRGBAColourHandle")] IntPtr colourTint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_createImageRectWithNothing([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtImageRectHandle *")] IntPtr* outputImageRect, NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("NrtRGBAColourHandle")] IntPtr colourTint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_createBasicFillRect([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtBasicFillRectHandle *")] IntPtr* outputBasicFillRect, NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_createTextRect([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtTextRectHandle *")] IntPtr* outputTextRect, NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig, float fontSize, [NativeTypeName("const char *")] sbyte* fontFilePath);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_getCamera([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtCameraHandle *")] IntPtr* outputCamera);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_beginFrame([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_endFrame([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_setBackgroundColour([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtRGBAColourHandle")] IntPtr colour);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_getTextureWithNothing([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtTextureHandle *")] IntPtr* outputTexture);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_getTextureWithFile([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtTextureHandle *")] IntPtr* outputTexture, [NativeTypeName("const char *")] sbyte* fileTarget);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_getFontSet([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtFontSetHandle *")] IntPtr* outputFontSet, [NativeTypeName("const char *")] sbyte* fileTarget, float fontSize);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderingService_destroy([NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtRGBAColourHandle")]
        public static extern IntPtr Nrt_RGBAColour_Create([NativeTypeName("int32_t")] int r, [NativeTypeName("int32_t")] int g, [NativeTypeName("int32_t")] int b, [NativeTypeName("int32_t")] int a);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_RGBAColour_getR([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RGBAColour_setR([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig, [NativeTypeName("int32_t")] int inputValue);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_RGBAColour_getG([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RGBAColour_setG([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig, [NativeTypeName("int32_t")] int inputValue);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_RGBAColour_getB([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RGBAColour_setB([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig, [NativeTypeName("int32_t")] int inputValue);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_RGBAColour_getA([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RGBAColour_setA([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig, [NativeTypeName("int32_t")] int inputValue);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_RGBAColour_getRScalar([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_RGBAColour_getGScalar([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_RGBAColour_getBScalar([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_RGBAColour_getAScalar([NativeTypeName("NrtRGBAColourHandle")] IntPtr colourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RGBAColour_destroy([NativeTypeName("NrtRGBAColourHandle")] IntPtr param0);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtTransform Nrt_TextRect_getTransform([NativeTypeName("NrtTextRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_setTransform([NativeTypeName("NrtTextRectHandle")] IntPtr rect, NrtTransform inputTransform);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_TextRect_getLayer([NativeTypeName("NrtTextRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_setLayer([NativeTypeName("NrtTextRectHandle")] IntPtr rect, [NativeTypeName("int32_t")] int inputLayer);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_TextRect_getActive([NativeTypeName("NrtTextRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_setActive([NativeTypeName("NrtTextRectHandle")] IntPtr rect, NrtBool inputBool);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_executeObjectBehaviour([NativeTypeName("NrtTextRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_getColourConfig([NativeTypeName("NrtTextRectHandle")] IntPtr rect, [NativeTypeName("NrtRGBAColourHandle *")] IntPtr* outputColourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_setColourConfig([NativeTypeName("NrtTextRectHandle")] IntPtr rect, [NativeTypeName("NrtRGBAColourHandle")] IntPtr inputColourConfig);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_TextRect_getText([NativeTypeName("NrtTextRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_setText([NativeTypeName("NrtTextRectHandle")] IntPtr rect, [NativeTypeName("const char *")] sbyte* inputText);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_getFontSet([NativeTypeName("NrtTextRectHandle")] IntPtr rect, [NativeTypeName("NrtFontSetHandle *")] IntPtr* outputFontSet);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_setFontSet([NativeTypeName("NrtTextRectHandle")] IntPtr rect, [NativeTypeName("NrtFontSetHandle")] IntPtr inputFontSet);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_getAsRenderObjectPtr([NativeTypeName("NrtTextRectHandle")] IntPtr rect, [NativeTypeName("NrtRenderObjectHandle *")] IntPtr* outputRenderObject);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_TextRect_destroy([NativeTypeName("NrtTextRectHandle")] IntPtr rect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Texture_loadPngAsTexture([NativeTypeName("NrtTextureHandle")] IntPtr targetTexture, [NativeTypeName("const char *")] sbyte* file);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_Texture_getTextureFile([NativeTypeName("NrtTextureHandle")] IntPtr targetTexture);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_Texture_getSize([NativeTypeName("NrtTextureHandle")] IntPtr targetTexture);
    }
}
