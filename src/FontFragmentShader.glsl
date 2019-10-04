#version 330 core
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