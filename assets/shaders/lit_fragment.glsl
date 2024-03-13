#version 330 core

struct material
{
    vec3 albedo;
    sampler2D albedo_texture;
    vec3 specular;
    sampler2D specular_map;
    float shininess;

    bool sample_albedo;
    bool sample_specular;
};

uniform material u_material;

struct base_light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

//    vec3 direction;
//    
//    float constant;
//    float linear;
//    float quadratic;
//
//    float angle_cos;
//    float outer_angle_cos;
};

struct directional_light
{
    base_light light;
    vec3 direction;
};

uniform directional_light u_directional_light;
uniform vec3 camera_position;


in vec3 fragment_position;
in vec3 normal;
in vec2 uv;

out vec4 o_fragment_colour;

vec3 get_albedo()
{
    vec3 albedo = u_material.albedo;
    if(u_material.sample_albedo)
    {
        albedo *= vec3(texture(u_material.albedo_texture, uv));
    }
    
    return albedo;
}

vec3 get_specular()
{
    vec3 specular = u_material.specular;
    if(u_material.sample_specular)
    {
        specular *= vec3(texture(u_material.specular_map, uv));
    }

    return specular;
}

vec3 calculate_directional_light(directional_light light, vec3 normal, vec3 view_direction)
{
    vec3 to_light = normalize(-light.direction);

    // Diffuse
    float diffuse_factor = max(dot(normal, to_light), 0.0);
    vec3 diffuse = light.light.diffuse * diffuse_factor * get_albedo();

    // Specular
    vec3 reflection_direction = reflect(-to_light, normal);
    float specular_factor = pow(max(dot(view_direction, reflection_direction), 0.0), u_material.shininess);
    vec3 specular = light.light.specular * specular_factor * get_specular();

    // Ambient
    vec3 ambient = light.light.ambient * get_albedo();

    return (ambient + diffuse + specular);

}

void main()
{
//    
//    
//    // Diffuse
//    // point light
//    vec3 to_light = normalize(u_light.position - fragment_position);
//    // point light
////    float distance = length(u_light.position - fragment_position);
////    float attenuation = 1.0 / (u_light.constant + u_light.linear * distance + u_light.quadratic * (distance * distance));
//
//    // spot
//    float theta = dot(to_light, normalize(-u_light.direction));
//    float epsilon = u_light.angle_cos - u_light.outer_angle_cos;
//    float intensity = clamp((theta - u_light.outer_angle_cos) / epsilon, 0.0, 1.0);
//
//    // directional light
//    //vec3 to_light = normalize(-u_light.direction);
//    float diffuse_strength = max(dot(normal, to_light), 0.0);
//    
//    if(u_material.sample_albedo)
//    {
//        diffuse = vec3(texture(u_material.albedo_texture, uv)) * diffuse_strength * u_light.diffuse * u_material.albedo;
//        // Ambient
//        ambient = vec3(texture(u_material.albedo_texture, uv)) * u_light.ambient;
//    }
//    else
//    {
//        diffuse = u_material.albedo * diffuse_strength * u_light.diffuse;
//        // Ambient
//        ambient = u_material.albedo * u_light.ambient;
//    } 
//
//    // Specular
//    
//    
//
//    // point light
////    ambient *= attenuation;
////    diffuse *= attenuation;
////    specular *= attenuation;
//
//// spot light
//    diffuse *= intensity;
//    specular *= intensity;

    //=============================================================
    vec3 output = vec3(0.0);
    vec3 view_direction = normalize(camera_position - fragment_position);

    output += calculate_directional_light(u_directional_light, normal, view_direction);
    //output += 1.;
//    for(int i = 0; i < point_light_count; i++)
//    {
//        output += calculate_point_light(i);
//    }

    //output += calculate_spot_light();

    o_fragment_colour = vec4(output, 1.0);
}