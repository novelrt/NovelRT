#version 330 core
out vec4 fragColour;

in vec2 texCoord;
in vec4 colourTint;

uniform sampler2D ourTexture;

void main()
{
    fragColour = texture(ourTexture, texCoord) * colourTint;
}