// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See License.md in the repository root for more information.

#include "ImguiTypes.hlsl"

cbuffer FrameData : register(b0)
{
row_major matrix frameTransform;
};

PSInput main(VSInput input)
{
    PSInput output;
    output.position = float4(input.position, 0.0f, 1.0f);
    output.position = mul(output.position, frameTransform);
    output.uv = input.uv;
    output.colourTint = input.colourTint;
    return output;
}
