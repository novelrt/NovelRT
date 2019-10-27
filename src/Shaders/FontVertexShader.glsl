#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColourTint;

//out vec4 ourColor;
out vec2 texCoord;
out vec4 colourTint;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    texCoord = aTexCoord;
    colourTint = aColourTint;
}