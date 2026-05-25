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
    row_major float4x4 model;
    float4 tint;
};

struct CameraConstantBuffer
{
    row_major float4x4 view;
    row_major float4x4 projection;
};

[[vk::push_constant]]
SpritePushConstant pushConstant;

[[vk::binding(1, 0)]]
ConstantBuffer<CameraConstantBuffer> camera : register(b0);

VSOutput main(VSInput input)
{
    VSOutput output;
    float4 worldPos = mul(float4(input.Position, 1.0f), pushConstant.model);
    output.Position = mul(mul(worldPos, camera.view), camera.projection);
    output.UV = input.UV;
    output.Tint = pushConstant.tint;
    return output;
}