#version 330 core

//in vec3 vertex_colour;
in vec2 uv;

uniform sampler2D sample_texture;

out vec4 fragment_colour;

const float offset = 1.0 / 300f; // TODO should this be based on screen/texture size?

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9] = float[](
        1, 2, 1,
        2, 4, 2,
        1, 2, 1
    );

    float total = 0.0;
    for (int i = 0; i < 9; i++)
    {
        total += kernel[i];
    }

    vec3 samples[9];
    for (int i = 0; i < 9; i++)
    {
        samples[i] = vec3(texture(sample_texture, uv.st + offsets[i]));
    }

    vec3 colour = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        colour += samples[i] * kernel[i] / total;
    }
    fragment_colour = vec4(colour, 1.0);
}