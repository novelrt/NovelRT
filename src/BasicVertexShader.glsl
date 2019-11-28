#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;

layout (std140) uniform FinalViewMatrixBuffer {
  mat4 modelViewProjection
};

out vec4 fragmentColour;

void main(){
    vec4 vertexPosition4 = vec4(vertexPosition, 1.0f);
    gl_Position = vertexPosition4 * modelViewProjection;
    fragmentColour = vertexColour;
}
