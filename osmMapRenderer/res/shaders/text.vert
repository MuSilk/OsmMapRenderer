#version 330 core
layout (location=0) in vec4 data;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position=projection*view*model*vec4(data.xy,0.0,1.0);
    TexCoord=data.zw;
}
