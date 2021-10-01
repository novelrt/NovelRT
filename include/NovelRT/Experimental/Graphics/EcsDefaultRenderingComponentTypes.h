// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_ECSDEFAULTRENDERINGCOMPONENTTYPES_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_ECSDEFAULTRENDERINGCOMPONENTTYPES_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    using BindingIndex = uint32_t;

    struct RenderComponent
    {
        size_t meshDataIndex = 0;
        int32_t renderLayer = 0;
        NovelRT::Graphics::RGBAConfig colourTint = NovelRT::Graphics::RGBAConfig(0, 0, 0, 0);
    };

    struct ShaderProgramComponent
    {
        size_t shaderProgramDataIndex = 0;
        size_t entityShaderBindingIdsIndex = 0;
    };

    struct BoolShaderDescriptorComponent
    {
        BindingIndex bindingLocation = 0;
        bool value = false;
    };

    struct IntShaderDescriptorComponent
    {
        BindingIndex bindingLocation = 0;
        int32_t value = 0;
    };

    struct UIntShaderDescriptorComponent
    {
        BindingIndex bindingLocation = 0;
        uint32_t value = 0;
    };

    struct FloatShaderDescriptorComponent
    {
        BindingIndex bindingLocation = 0;
        float value = 0.0f;
    };

    struct DoubleShaderDescriptorComponent
    {
        BindingIndex bindingLocation = 0;
        double value = 0.0f;
    };

    struct Vector2FShaderDescriptorComponent
    {
        BindingIndex bindingLocation = 0;
        Maths::GeoVector2F value = Maths::GeoVector2F::zero();
    };

    struct Vector3FShaderDescriptorComponent
    {
        BindingIndex bindingLocation = 0;
        Maths::GeoVector3F value = Maths::GeoVector2F::zero();
    };

    struct Vector4FShaderDescriptorComponent
    {
        BindingIndex bindingLocation = 0;
        Maths::GeoVector4F value = Maths::GeoVector2F::zero();
    };

    struct GeoMatrix4x4FShaderDescriptorComponent
    {
        BindingIndex bindingLocation = 0;
        Maths::GeoMatrix4x4F value = Maths::GeoMatrix4x4F::getDefaultIdentity();
    };

}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_ECSDEFAULTRENDERINGCOMPONENTTYPES_H
