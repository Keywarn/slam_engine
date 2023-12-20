#version 330 core

uniform vec3 albedo;
uniform vec3 light;

out vec4 fragment_colour;

void main()
{
    fragment_colour = vec4(albedo * light, 1.0);
}