// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#version 330
precision mediump float;
in vec4 fragmentColour;
out vec4 colour;
void main(){
    colour = fragmentColour;
}
