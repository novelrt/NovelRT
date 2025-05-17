// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#version 300 es

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColourTint;

layout (std140) uniform finalViewMatrixBuffer {
  mat4 modelViewProjection;
};

out vec2 texCoord;
out vec4 colourTint;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0) * modelViewProjection;
    texCoord = aTexCoord;
    colourTint = aColourTint;
}
