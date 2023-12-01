#version 330 core

in vec3 vertex_colour;

out vec4 fragment_colour;

void main()
{
    fragment_colour = vec4(vertex_colour, 1.0);
}