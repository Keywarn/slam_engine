#version 330 core

in vec3 uv;

uniform samplerCube skybox;

out vec4 fragment_colour;

void main()
{    
    fragment_colour = texture(skybox, uv);
}