#version 460 core

layout (location = 0) in vec4 vertex;

layout (std140) uniform Camera
{
    mat4 proj;
};

uniform mat4 model;

void main()
{
    //TexCoords = vertex.zw;
    gl_Position = proj * model * vec4(vertex.xy, 0.0, 1.0);
}