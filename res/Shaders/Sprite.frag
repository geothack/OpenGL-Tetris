#version 460 core

out vec4 color;

uniform float Red;
uniform float Green;
uniform float Blue;

void main()
{    
    color = vec4(Red,Green,Blue, 1.0);
    //* texture(image, TexCoords);
}  