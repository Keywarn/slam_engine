#include "scene.h"

namespace slam
{

entity_id scene::new_entity()
{
    m_entities.push_back({ m_entities.size(), component_mask() });
    return m_entities.back().m_id;
}

template<typename component_type>
component_type* scene::assign_component(entity_id id)
{
    int component_id = get_component_id<component_id>();

    if (m_component_pools.size() <= component_id) // Expand the pool
    {
        component_pool.resize(component_id + 1, nullptr);
    }
    if (m_component_pools[component_id] == nullptr) // Create pool for new component
    {
        m_component_pools[component_id] = new component_pool(sizeof(component_type));
    }

    compontnent_type* component = new (m_component_pools[component_id]->get(component_id)) component_type();

    m_entities[id].m_mask.set(component_id);
    return component;
}

template<typename component_type>
component_type* scene::get_component(entity_id id)
{
    int component_id = get_component_id<component_type>();
    if (!m_entities[id].mask.test(component_id))
    {
        // TODO error validation? Or maybe we are fine returning null and it is on the user to check....
        return nullptr;
    }

    return static_cast<component_type*>(m_component_pools[component_id]->get(id));
}
};
