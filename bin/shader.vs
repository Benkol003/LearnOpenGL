#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTexPos;

uniform mat4 uTransform;

out vec2 vTexPos;

void main() {
    gl_Position = uTransform*vec4(aPos.x,aPos.y,aPos.z,1.0);
    vTexPos=aTexPos;
}
