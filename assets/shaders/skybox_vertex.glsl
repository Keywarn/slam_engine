#version 330 core
layout (location = 0) in vec3 a_position;

uniform mat4 projection;
uniform mat4 view;

out vec3 uv;

void main()
{
    uv = a_position;
    gl_Position = (projection * view * vec4(a_position, 1.0)).xyww;
}  