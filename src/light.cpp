#include "light.h"

namespace render_engine
{
light::light(glm::vec3 position, glm::vec3 colour, float strength)
    : m_position(position)
    , m_colour(colour)
    , m_strength(strength)
{

}

directional_light::directional_light(glm::vec3 direction, glm::vec3 position, glm::vec3 colour, float strength)
    : light(position, colour, strength)
    , m_direction(direction)
{

}
}