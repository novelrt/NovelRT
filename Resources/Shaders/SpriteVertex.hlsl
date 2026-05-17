// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See License.md in the repository root for more information.

struct VSInput
{
    float3 Position : POSITION;
    float2 UV : TEXCOORD0;
};

struct VSOutput
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
    float4 Tint : COLOR0;
};

struct SpritePushConstant
{
    float4x4 model;
    float4 tint;
};

[[vk::push_constant]]
SpritePushConstant pushConstant;

VSOutput main(VSInput input)
{
    VSOutput output;
    output.Position = mul(float4(input.Position, 1.0f), pushConstant.model);
    output.UV = input.UV;
    output.Tint = pushConstant.tint;
    return output;
}