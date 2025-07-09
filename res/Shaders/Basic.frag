#version 460 core

out vec4 FragColor;

uniform float Red;
uniform float Green;
uniform float Blue;

void main()
{
	FragColor = vec4(Red,Green,Blue,1.0);
}