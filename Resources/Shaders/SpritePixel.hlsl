// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See License.md in the repository root for more information.

struct PSInput
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
    float4 Tint : COLOR0;
};

[[vk::binding(0, 0)]]
Texture2D spriteTexture : register(t0);

[[vk::binding(1, 0)]]
SamplerState spriteSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
    return spriteTexture.Sample(spriteSampler, input.UV) * input.Tint;
}
