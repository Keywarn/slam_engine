#version 330 core

struct material {
    vec3 albedo;
};

uniform material u_material;

out vec4 fragment_colour;

void main()
{
    fragment_colour = vec4(u_material.albedo, 1.0);
}