#version 330 core

//in vec3 vertex_colour;
in vec2 uv;

uniform sampler2D sample_texture;

out vec4 fragment_colour;

const float gamma = 2.2;

void main()
{

    fragment_colour = texture(sample_texture, uv);
    fragment_colour.rgb = pow(fragment_colour.rgb, vec3(1.0/gamma));
}