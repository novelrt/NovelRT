// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_ECSDEFAULTRENDERINGCOMPONENTTYPES_H
#define NOVELRT_ECS_GRAPHICS_ECSDEFAULTRENDERINGCOMPONENTTYPES_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    using BindingIndex = uint32_t;

    struct RenderComponent
    {
        Atom vertexDataId = 0;
        Atom textureId = 0;
        Atom pipelineId = 0;
        Atom primitiveInfoId = 0;
        bool markedForDeletion = false;

        inline RenderComponent& operator+=(const RenderComponent& other)
        {
            vertexDataId = other.vertexDataId;
            textureId = other.textureId;
            pipelineId = other.pipelineId;
            primitiveInfoId = other.primitiveInfoId;
            markedForDeletion = other.markedForDeletion;
            return *this;
        }

        inline bool operator==(const RenderComponent& other) const noexcept
        {
            return ((vertexDataId == other.vertexDataId) && (textureId == other.textureId) &&
                    (pipelineId == other.pipelineId)) &&
                   (markedForDeletion == other.markedForDeletion);
        }

        inline bool operator!=(const RenderComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };

    // TODO: I don't know how to use these given how GraphicsPrimitive currently works quite yet.
    /*
    struct RGBAColourShaderDescriptorComponent
    {
        NovelRT::Graphics::RGBAColour value = NovelRT::Graphics::RGBAColour(0, 0, 0, 0);
    };

    struct BoolShaderDescriptorComponent
    {
        bool value = false;
    };

    struct IntShaderDescriptorComponent
    {
        int32_t value = 0;
    };

    struct UIntShaderDescriptorComponent
    {
        uint32_t value = 0;
    };

    struct FloatShaderDescriptorComponent
    {
        float value = 0.0f;
    };

    struct DoubleShaderDescriptorComponent
    {
        double value = 0.0f;
    };

    struct Vector2FShaderDescriptorComponent
    {
        Maths::GeoVector2F value = Maths::GeoVector2F::zero();
    };

    struct Vector3FShaderDescriptorComponent
    {
        Maths::GeoVector3F value = Maths::GeoVector2F::zero();
    };

    struct Vector4FShaderDescriptorComponent
    {
        Maths::GeoVector4F value = Maths::GeoVector2F::zero();
    };

    struct GeoMatrix4x4FShaderDescriptorComponent
    {
        Maths::GeoMatrix4x4F value = Maths::GeoMatrix4x4F::getDefaultIdentity();
    };
     */

}

#endif // !NOVELRT_ECS_GRAPHICS_ECSDEFAULTRENDERINGCOMPONENTTYPES_H
