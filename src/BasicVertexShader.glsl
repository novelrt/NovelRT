#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;

layout (std140) uniform finalViewMatrixBuffer {
  mat4 modelViewProjection
};

out vec4 fragmentColour;

void main(){
    gl_Position = vec4(vertexPosition, 1.0f) * modelViewProjection;
    fragmentColour = vertexColour;
}
