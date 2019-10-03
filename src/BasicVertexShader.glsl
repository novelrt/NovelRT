#version 330 core

layout(location = 0) uniform mat3 projectionView;
layout(location = 1) uniform mat3 modelTransform;
layout(location = 2) in vec3 vertexPositionModelSpace;
layout(location = 3) in vec4 vertexColour;

out vec4 fragmentColour;

void main(){
    gl_Position.xyz = vertexPositionModelSpace * modelTransform * projectionView;
    gl_Position.w = 1.0;
    fragmentColour = vertexColour;
}