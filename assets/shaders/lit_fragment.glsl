#version 330 core

uniform vec3 albedo;
uniform vec3 light_colour;
uniform vec3 light_position;
uniform vec3 camera_position;

in vec3 fragment_position;
in vec3 normal;

out vec4 fragment_colour;

void main()
{
//TODO These would be part of the material instead
    float ambient_strength = 0.1;
    float specular_strength = 0.5;
    float shininess = 32;

    vec3 ambient = ambient_strength * light_colour;

    vec3 to_light = normalize(light_position - fragment_position);
    float diffuse_strength = max(dot(normal, to_light), 0.0);
    vec3 diffuse = diffuse_strength * light_colour;

    vec3 to_camera = normalize(camera_position - fragment_position);
    vec3 reflection_direction = reflect(-to_light, normal);
    float specular_factor = pow(max(dot(to_camera, reflection_direction), 0.0), shininess);
    vec3 specular = specular_factor * specular_strength * light_colour;

    fragment_colour = vec4(albedo * (ambient + diffuse + specular), 1.0);
}