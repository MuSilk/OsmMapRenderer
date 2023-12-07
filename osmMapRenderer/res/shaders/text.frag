#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec3 color;
uniform sampler2D image;

void main(){
    FragColor=texture(image,TexCoord)*vec4(color,1.0);
}
