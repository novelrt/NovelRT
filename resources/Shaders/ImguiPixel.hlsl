// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See License.md in the repository root for more information.

#include "ImguiTypes.hlsl"

Texture2D textureInput : register(t2);
SamplerState samplerInput : register(s2);

float4 main(PSInput input) : SV_Target
{
    return textureInput.Sample(samplerInput, input.uv);
}
