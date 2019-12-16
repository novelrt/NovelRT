#version 330 core

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
