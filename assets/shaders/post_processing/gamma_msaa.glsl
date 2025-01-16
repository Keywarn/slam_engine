#version 330 core

in vec2 uv;

uniform sampler2DMS sample_textureMS;

out vec4 fragment_colour;

const float gamma = 2.2;

void main()
{
    // Need integer uv, since texture is the same size as the screen we can use the fragment co-ord
    ivec2 iuv = ivec2(gl_FragCoord.x, gl_FragCoord.y);
    // Just do an average of the 4 samples... 
    fragment_colour = (texelFetch(sample_textureMS, iuv, 3) + 
                      texelFetch(sample_textureMS, iuv, 3) +
                      texelFetch(sample_textureMS, iuv, 3) +
                      texelFetch(sample_textureMS, iuv, 3)) * 0.25;
    fragment_colour.rgb = pow(fragment_colour.rgb, vec3(1.0/gamma));
}