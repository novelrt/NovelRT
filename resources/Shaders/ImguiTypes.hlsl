// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See License.md in the repository root for more information.

struct VSInput
{
    float2 position : POSITION;
    float2 uv : TEXCOORD;
    float4 colourTint : COLOR;
};

struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
    float4 colourTint : COLOR;
};
