#version 330 core

//in vec3 vertex_colour;
in vec2 uv;

uniform sampler2D sample_texture;

out vec4 fragment_colour;

void main()
{
    fragment_colour = texture(sample_texture, uv);
}