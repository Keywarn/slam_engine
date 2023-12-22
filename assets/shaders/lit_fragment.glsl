#version 330 core

struct material {
    vec3 albedo;
    vec3 ambient;
    vec3 specular;
    float shininess;
};

uniform material u_material;

struct light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform light u_light;

uniform vec3 camera_position;

in vec3 fragment_position;
in vec3 normal;

out vec4 fragment_colour;

void main()
{
    // Ambient
    vec3 ambient = u_material.ambient * u_light.ambient;

    // Diffuse
    vec3 to_light = normalize(u_light.position - fragment_position);
    float diffuse_strength = max(dot(normal, to_light), 0.0);
    
    vec3 diffuse = u_material.albedo * diffuse_strength * u_light.diffuse;

    // Specular
    vec3 to_camera = normalize(camera_position - fragment_position);
    vec3 reflection_direction = reflect(-to_light, normal);
    float specular_factor = pow(max(dot(to_camera, reflection_direction), 0.0), u_material.shininess);
    
    vec3 specular = specular_factor * u_material.specular * u_light.specular;

    fragment_colour = vec4((ambient + diffuse + specular), 1.0);
}