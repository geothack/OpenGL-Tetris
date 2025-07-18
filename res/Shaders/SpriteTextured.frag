#version 460 core

out vec4 color;

in vec2 TexCoords;

layout (location = 0) uniform sampler2D image;

uniform float Alpha;

void main()
{    
    color = vec4(texture(image, TexCoords).rgb,1.0);
}  