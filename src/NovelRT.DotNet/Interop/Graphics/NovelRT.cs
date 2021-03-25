// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtRGBAConfig")]
        public static extern IntPtr Nrt_RGBAConfig_Create([NativeTypeName("int32_t")] int r, [NativeTypeName("int32_t")] int g, [NativeTypeName("int32_t")] int b, [NativeTypeName("int32_t")] int a);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_RGBAConfig_getR([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RGBAConfig_setR([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig, [NativeTypeName("int32_t")] int inputValue);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_RGBAConfig_getG([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RGBAConfig_setG([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig, [NativeTypeName("int32_t")] int inputValue);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_RGBAConfig_getB([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RGBAConfig_setB([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig, [NativeTypeName("int32_t")] int inputValue);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_RGBAConfig_getA([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RGBAConfig_setA([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig, [NativeTypeName("int32_t")] int inputValue);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern float Nrt_RGBAConfig_getRScalar([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern float Nrt_RGBAConfig_getGScalar([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern float Nrt_RGBAConfig_getBScalar([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern float Nrt_RGBAConfig_getAScalar([NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RGBAConfig_destroy([NativeTypeName("NrtRGBAConfig")] IntPtr param0);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_create([NativeTypeName("NrtWindowingService")] IntPtr windowingService, [NativeTypeName("NrtRenderingService *")] IntPtr* outputRenderingService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_initialiseRendering([NativeTypeName("NrtRenderingService")] IntPtr renderingService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_tearDown([NativeTypeName("NrtRenderingService")] IntPtr renderingService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_createImageRectWithFile([NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtImageRect *")] IntPtr* outputImageRect, NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("const char *")] sbyte* filePath, [NativeTypeName("NrtRGBAConfig")] IntPtr colourTint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_createImageRectWithNothing([NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtImageRect *")] IntPtr* outputImageRect, NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("NrtRGBAConfig")] IntPtr colourTint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_createBasicFillRect([NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtBasicFillRect *")] IntPtr* outputBasicFillRect, NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_createTextRect([NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtTextRect *")] IntPtr* outputTextRect, NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("NrtRGBAConfig")] IntPtr colourConfig, float fontSize, [NativeTypeName("const char *")] sbyte* fontFilePath);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_getCamera([NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtCamera *")] IntPtr* outputCamera);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_beginFrame([NativeTypeName("NrtRenderingService")] IntPtr renderingService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_endFrame([NativeTypeName("NrtRenderingService")] IntPtr renderingService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_setBackgroundColour([NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtRGBAConfig")] IntPtr colour);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_getTextureWithNothing([NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtTexture *")] IntPtr* outputTexture);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_getTextureWithFile([NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtTexture *")] IntPtr* outputTexture, [NativeTypeName("const char *")] sbyte* fileTarget);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_getFontSet([NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtFontSet *")] IntPtr* outputFontSet, [NativeTypeName("const char *")] sbyte* fileTarget, float fontSize, [NativeTypeName("const char **")] sbyte** errorMessage);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderingService_destroy([NativeTypeName("NrtRenderingService")] IntPtr renderingService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtCamera")]
        public static extern IntPtr Nrt_Camera_create();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_Camera_getViewMatrix([NativeTypeName("NrtCamera")] IntPtr camera);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Camera_setViewMatrix([NativeTypeName("NrtCamera")] IntPtr camera, NrtGeoMatrix4x4F inputMatrix);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_Camera_getProjectionMatrix([NativeTypeName("NrtCamera")] IntPtr camera);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Camera_setProjectionMatrix([NativeTypeName("NrtCamera")] IntPtr camera, NrtGeoMatrix4x4F inputMatrix);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_Camera_getCameraUboMatrix([NativeTypeName("NrtCamera")] IntPtr camera);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtCameraFrameState Nrt_Camera_getFrameState([NativeTypeName("NrtCamera")] IntPtr camera);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Camera_setForceResizeCallback([NativeTypeName("NrtCamera")] IntPtr camera, [NativeTypeName("void (*)(NrtCamera, NrtGeoVector2F)")] delegate* unmanaged<IntPtr, NrtGeoVector2F, void> callback);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtCamera")]
        public static extern IntPtr Nrt_Camera_createDefaultOrthographicProjection(NrtGeoVector2F windowSize);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtCamera")]
        public static extern IntPtr Nrt_Camera_createDefaultPerspectiveProjection(NrtGeoVector2F windowSize);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Camera_destroy([NativeTypeName("NrtCamera")] IntPtr camera);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Texture_loadPngAsTexture([NativeTypeName("NrtTexture")] IntPtr targetTexture, [NativeTypeName("const char *")] sbyte* file);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_Texture_getTextureFile([NativeTypeName("NrtTexture")] IntPtr targetTexture);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_Texture_getSize([NativeTypeName("NrtTexture")] IntPtr targetTexture);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_FontSet_loadFontAsTextureSet([NativeTypeName("NrtFontSet")] IntPtr fontSet, [NativeTypeName("const char *")] sbyte* file, float fontSize);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_FontSet_getFontFile([NativeTypeName("NrtFontSet")] IntPtr fontSet, [NativeTypeName("const char **")] sbyte** outputFontFile);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_FontSet_getFontSize([NativeTypeName("NrtFontSet")] IntPtr fontSet, [NativeTypeName("float *")] float* outputFontSize);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_BasicFillRect_getTransform([NativeTypeName("NrtBasicFillRect")] IntPtr rect, [NativeTypeName("NrtTransform *")] NrtTransform* outputTransform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_BasicFillRect_setTransform([NativeTypeName("NrtBasicFillRect")] IntPtr rect, NrtTransform inputTransform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_BasicFillRect_getLayer([NativeTypeName("NrtBasicFillRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_BasicFillRect_setLayer([NativeTypeName("NrtBasicFillRect")] IntPtr rect, [NativeTypeName("int32_t")] int inputLayer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_BasicFillRect_getActive([NativeTypeName("NrtBasicFillRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_BasicFillRect_setActive([NativeTypeName("NrtBasicFillRect")] IntPtr rect, [NativeTypeName("NrtBool")] int inputBool);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_BasicFillRect_executeObjectBehaviour([NativeTypeName("NrtBasicFillRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_BasicFillRect_getColourConfig([NativeTypeName("NrtBasicFillRect")] IntPtr rect, [NativeTypeName("NrtRGBAConfig *")] IntPtr* outputColourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_BasicFillRect_setColourConfig([NativeTypeName("NrtBasicFillRect")] IntPtr rect, [NativeTypeName("NrtRGBAConfig")] IntPtr inputColourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_BasicFillRect_getAsRenderObjectPtr([NativeTypeName("NrtBasicFillRect")] IntPtr rect, [NativeTypeName("NrtRenderObject *")] IntPtr* outputRenderObject);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtTransform Nrt_ImageRect_getTransform([NativeTypeName("NrtImageRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ImageRect_setTransform([NativeTypeName("NrtImageRect")] IntPtr rect, NrtTransform inputTransform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_ImageRect_getLayer([NativeTypeName("NrtImageRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ImageRect_setLayer([NativeTypeName("NrtImageRect")] IntPtr rect, [NativeTypeName("int32_t")] int inputLayer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_ImageRect_getActive([NativeTypeName("NrtImageRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ImageRect_setActive([NativeTypeName("NrtImageRect")] IntPtr rect, [NativeTypeName("NrtBool")] int inputBool);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ImageRect_executeObjectBehaviour([NativeTypeName("NrtImageRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ImageRect_getTexture([NativeTypeName("NrtImageRect")] IntPtr rect, [NativeTypeName("NrtTexture *")] IntPtr* outputTexture);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ImageRect_setTexture([NativeTypeName("NrtImageRect")] IntPtr rect, [NativeTypeName("NrtTexture")] IntPtr inputTexture);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ImageRect_getColourTint([NativeTypeName("NrtImageRect")] IntPtr rect, [NativeTypeName("NrtRGBAConfig *")] IntPtr* outputColourTint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ImageRect_setColourTint([NativeTypeName("NrtImageRect")] IntPtr rect, [NativeTypeName("NrtRGBAConfig")] IntPtr inputColourTint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ImageRect_getAsRenderObjectPtr([NativeTypeName("NrtImageRect")] IntPtr rect, [NativeTypeName("NrtRenderObject *")] IntPtr* outputRenderObject);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_getTransform([NativeTypeName("NrtTextRect")] IntPtr rect, [NativeTypeName("NrtTransform *")] NrtTransform* outputTransform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_setTransform([NativeTypeName("NrtTextRect")] IntPtr rect, NrtTransform inputTransform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_TextRect_getLayer([NativeTypeName("NrtTextRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_setLayer([NativeTypeName("NrtTextRect")] IntPtr rect, [NativeTypeName("int32_t")] int inputLayer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_TextRect_getActive([NativeTypeName("NrtTextRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_setActive([NativeTypeName("NrtTextRect")] IntPtr rect, [NativeTypeName("NrtBool")] int inputBool);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_executeObjectBehaviour([NativeTypeName("NrtTextRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_getColourConfig([NativeTypeName("NrtTextRect")] IntPtr rect, [NativeTypeName("NrtRGBAConfig *")] IntPtr* outputColourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_setColourConfig([NativeTypeName("NrtTextRect")] IntPtr rect, [NativeTypeName("NrtRGBAConfig")] IntPtr inputColourConfig);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_TextRect_getText([NativeTypeName("NrtTextRect")] IntPtr rect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_setText([NativeTypeName("NrtTextRect")] IntPtr rect, [NativeTypeName("const char *")] sbyte* inputText);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_getFontSet([NativeTypeName("NrtTextRect")] IntPtr rect, [NativeTypeName("NrtFontSet *")] IntPtr* outputFontSet);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_setFontSet([NativeTypeName("NrtTextRect")] IntPtr rect, [NativeTypeName("NrtFontSet")] IntPtr inputFontSet);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_TextRect_getAsRenderObjectPtr([NativeTypeName("NrtTextRect")] IntPtr rect, [NativeTypeName("NrtRenderObject *")] IntPtr* outputRenderObject);
    }
}
