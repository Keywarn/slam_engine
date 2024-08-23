#version 330 core

#define MAX_NUM_POINT_LIGHTS 4

#define SHADOW_BIAS_MAX 0.001
#define SHADOW_BIAS_MIN 0.0005

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
//
//    float angle_cos;
//    float outer_angle_cos;
//direction
};

struct directional_light
{
    base_light light;
    vec3 direction;
};

struct point_light
{
    base_light light;
    float constant;
    float linear;
    float quadratic;
};

struct spot_light
{
    base_light light;
    float angle_cos;
    float outer_angle_cos;
    vec3 direction;
};

uniform directional_light u_directional_light;
uniform point_light u_point_lights[MAX_NUM_POINT_LIGHTS];
uniform spot_light u_spot_light;
uniform sampler2D u_shadow_map;

uniform vec3 u_camera_position;

in vec3 fragment_position;
in vec3 normal;
in vec2 uv;
in vec4 fragment_position_light_space;

out vec4 fragment_colour;

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

float calculate_shadow(vec4 position_light_space, vec3 normal, vec3 to_light)
{
    // Perspective divide
    vec3 projected_coords = position_light_space.xyz / position_light_space.w;
    projected_coords = projected_coords * 0.5 + 0.5;
    float closest_depth = texture(u_shadow_map, projected_coords.xy).r;

    float bias = max(SHADOW_BIAS_MAX * (1.0 - dot(normal, to_light)), SHADOW_BIAS_MIN);
    float shadow = projected_coords.z - bias > closest_depth ? 1.0 : 0.0;

    return shadow;
}

vec3 calculate_directional_light(directional_light light, vec3 normal, vec3 view_direction)
{
    vec3 to_light = normalize(-light.direction);
    
    float shadow = calculate_shadow(fragment_position_light_space, normal, to_light);

    // Diffuse
    float diffuse_factor = max(dot(normal, to_light), 0.0);
    vec3 diffuse = light.light.diffuse * diffuse_factor * get_albedo();

    // Specular
    vec3 halfway_direction = normalize(to_light + view_direction);
    float specular_factor = pow(max(dot(normal, halfway_direction), 0.0), u_material.shininess);
    vec3 specular = light.light.specular * specular_factor * get_specular();

    // Ambient
    vec3 ambient = light.light.ambient * get_albedo();

    return (ambient + (1 - shadow) * (diffuse + specular));

}

vec3 calculate_point_light(point_light light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
    vec3 to_light = normalize(light.light.position - fragment_position);

    // Diffuse
    float diffuse_factor = max(dot(normal, to_light), 0.0);
    vec3 diffuse = light.light.diffuse * diffuse_factor * get_albedo();

    // Specular
    vec3 halfway_direction = normalize(to_light + view_direction);
    float specular_factor = pow(max(dot(normal, halfway_direction), 0.0), u_material.shininess);
    vec3 specular = light.light.specular * specular_factor * get_specular();
    
    // Ambient
    vec3 ambient = light.light.ambient * get_albedo();

    // Attenuation
    float distance = length(light.light.position - fragment_position);
    float attenuation = clamp(1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)), 0., 1.);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 calculate_spot_light(spot_light light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
    vec3 to_light = normalize(light.light.position - fragment_position);

    // Diffuse
    float diffuse_factor = max(dot(normal, to_light), 0.0);
    vec3 diffuse = light.light.diffuse * diffuse_factor * get_albedo();

    // Specular
    vec3 halfway_direction = normalize(to_light + view_direction);
    float specular_factor = pow(max(dot(normal, halfway_direction), 0.0), u_material.shininess);
    vec3 specular = light.light.specular * specular_factor * get_specular();

    // Intensity
    float theta = dot(to_light, normalize(-light.direction));
    float epsilon = light.angle_cos - light.outer_angle_cos;
    float intensity = clamp((theta - light.outer_angle_cos) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;

    return (diffuse + specular);
}

void main()
{
    vec3 output = vec3(0.0);
    vec3 view_direction = normalize(u_camera_position - fragment_position);

    output += calculate_directional_light(u_directional_light, normal, view_direction);

    for(int i = 0; i < MAX_NUM_POINT_LIGHTS; i++)
    {
        output += calculate_point_light(u_point_lights[i], normal, fragment_position, view_direction);
    }

    output += calculate_spot_light(u_spot_light, normal, fragment_position, view_direction);

    fragment_colour = vec4(output, 1.0);
}