#include "scene.h"

namespace slam
{

entity_id scene::new_entity()
{
    m_entities.push_back({ m_entities.size(), component_mask() });
    return m_entities.back().m_id;
}

template<typename component_type>
void scene::assign_component(entity_id id)
{
    int component_id = get_component_id<component_id>();
    m_entities[id].m_mask.set(component_id);
}
};
