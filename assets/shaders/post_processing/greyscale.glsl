#version 330 core

//in vec3 vertex_colour;
in vec2 uv;

uniform sampler2D sample_texture;

out vec4 fragment_colour;

void main()
{
    fragment_colour = texture(sample_texture, uv);

    // Weighted average to account for sensitivity to certain colours
    float average = 0.2126 * fragment_colour.r
                  + 0.7152 * fragment_colour.g
                  + 0.0722 * fragment_colour.b;

    fragment_colour = vec4(average, average, average, 1.0);
}