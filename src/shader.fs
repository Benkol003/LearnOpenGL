#version 330 core

in vec2 vTexPos;
out vec4 fColor;

uniform sampler2D texture0; //location binding = 0 by defualt, so Gl_TEXTURE0
//using (binding=...) requires #version 420
uniform sampler2D texture1;

void main() {
    fColor=mix( texture(texture0,vTexPos) , texture(texture1,vTexPos) ,0.5) ;
}
