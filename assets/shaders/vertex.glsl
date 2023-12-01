#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_colour;

out vec3 vertex_colour;

void main()
{
    gl_Position = vec4(a_position, 1.0);
    vertex_colour = a_colour;
}