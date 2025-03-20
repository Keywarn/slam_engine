#pragma once

#include <slam_ecs/component.h>

#include <glm/glm.hpp>

namespace slam {

class transform_component : public component
{
public:

    glm::vec3 m_position;
    glm::quat m_rotation;
};

}; // namespace cx
