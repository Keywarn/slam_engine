#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_colour;
layout (location = 2) in vec2 a_uv;

out vec3 vertex_colour;
out vec2 uv;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * transform * vec4(a_position, 1.0);
    vertex_colour = a_colour;
    uv = a_uv;
}