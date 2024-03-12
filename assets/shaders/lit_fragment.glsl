#version 330 core

struct material {
    vec3 albedo;
    sampler2D albedo_texture;
    vec3 specular;
    sampler2D specular_map;
    float shininess;

    bool sample_albedo;
    bool sample_specular;
};

uniform material u_material;

struct light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform light u_light;

uniform vec3 camera_position;

in vec3 fragment_position;
in vec3 normal;
in vec2 uv;

out vec4 fragment_colour;

void main()
{
    vec3 ambient, diffuse, specular;
    
    // Diffuse
    // point light
    vec3 to_light = normalize(u_light.position - fragment_position);
    float distance = length(u_light.position - fragment_position);
    float attenuation = 1.0 / (u_light.constant + u_light.linear * distance + u_light.quadratic * (distance * distance));


    // directional light
    //vec3 to_light = normalize(-u_light.direction);
    float diffuse_strength = max(dot(normal, to_light), 0.0);
    
    if(u_material.sample_albedo)
    {
        diffuse = vec3(texture(u_material.albedo_texture, uv)) * diffuse_strength * u_light.diffuse * u_material.albedo;
        // Ambient
        ambient = vec3(texture(u_material.albedo_texture, uv)) * u_light.ambient;
    }
    else
    {
        diffuse = u_material.albedo * diffuse_strength * u_light.diffuse;
        // Ambient
        ambient = u_material.albedo * u_light.ambient;
    } 

    // Specular
    vec3 to_camera = normalize(camera_position - fragment_position);
    vec3 reflection_direction = reflect(-to_light, normal);
    float specular_factor = pow(max(dot(to_camera, reflection_direction), 0.0), u_material.shininess);
    
    if(u_material.sample_specular)
    {
        specular = specular_factor * vec3(texture(u_material.specular_map, uv)) * u_light.specular;
    }
    else
    {
        specular = specular_factor * u_material.specular * u_light.specular;
    }

    // point light
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    fragment_colour = vec4((ambient + diffuse + specular), 1.0);
}