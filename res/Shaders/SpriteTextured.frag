#version 460 core

out vec4 color;

in vec2 TexCoords;

layout (location = 0) uniform sampler2D image;

void main()
{    
    color = texture(image, TexCoords);
}  