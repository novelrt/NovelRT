// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#version 300 es
precision mediump float;
out vec4 fragColor;

in vec2 texCoord;
in vec4 colourTint;

uniform sampler2D ourTexture;

void main()
{
    vec3 glyphColour = texture(ourTexture, texCoord).rgb;
    float alpha = glyphColour.r;
    fragColor = vec4(1, 1, 1, alpha)  * colourTint;
}
