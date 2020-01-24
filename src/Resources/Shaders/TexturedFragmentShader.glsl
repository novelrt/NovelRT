// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#version 330 core
out vec4 fragColour;

in vec2 texCoord;
in vec4 colourTint;

uniform sampler2D ourTexture;

void main()
{
    fragColour = texture(ourTexture, texCoord) * colourTint;
}
