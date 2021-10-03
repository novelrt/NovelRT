// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See License.md in the repository root for more information.
// Originally taken from the TerraFX repository. Licenced under the MIT Licence (MIT). See Licence.md in https://github.com/terrafx/terrafx for more information.

struct VSInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};
