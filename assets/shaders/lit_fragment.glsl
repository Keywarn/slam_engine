#version 330 core

uniform vec3 albedo;
uniform vec3 light;

out vec4 fragment_colour;

void main()
{
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light;
    fragment_colour = vec4(albedo * ambient, 1.0);
}