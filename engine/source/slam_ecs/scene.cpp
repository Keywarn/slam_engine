#include "scene.h"

namespace slam
{

entity_id scene::new_entity()
{
    if (!m_free_entities.empty())
    {
        entity_index index = m_free_entities.back();
        m_free_entities.pop_back();
        entity_id id = create_entity_id(index, get_entity_version(m_entities[index].m_id));
        m_entities[index].m_id = id;
        return m_entities[index].m_id;
    }
    m_entities.push_back({ m_entities.size(), component_mask() });
    return m_entities.back().m_id;
}

void scene::destroy_entity(entity_id id)
{
    if (m_entities[get_entity_index(id)].m_id != id)
    {
        // TODO this sould probably error as there is not information to check for a valid deletion being returned
        return;
    }

    entity_id new_id = create_entity_id(entity_index(-1), get_entity_version(id) + 1);
    m_entities[get_entity_index(id)].m_id = new_id;
    m_entities[get_entity_index(id)].m_mask.reset();
    m_free_entities.push_back(get_entity_index(id));
}

template<typename component_type>
component_type* scene::assign_component(entity_id id)
{
    if (m_entities[get_entity_index(id)].m_id != id)
    {
        return nullptr;
    }

    int component_id = get_component_id<component_id>();

    if (m_component_pools.size() <= component_id) // Expand the pool
    {
        m_component_pools.resize(component_id + 1, nullptr);
    }
    if (m_component_pools[component_id] == nullptr) // Create pool for new component
    {
        m_component_pools[component_id] = new component_pool(sizeof(component_type));
    }

    component_type* component = new (m_component_pools[component_id]->get(component_id)) component_type();

    m_entities[get_entity_index(id)].m_mask.set(component_id);
    return component;
}

template<typename component_type>
component_type* scene::get_component(entity_id id)
{
    if (m_entities[get_entity_index(id)].m_id != id)
    {
        return nullptr;
    }

    int component_id = get_component_id<component_type>();
    if (!m_entities[get_entity_index(id)].m_mask.test(component_id))
    {
        // TODO error validation? Or maybe we are fine returning null and it is on the user to check....
        return nullptr;
    }

    return static_cast<component_type*>(m_component_pools[component_id]->get(get_entity_index(id)));
}

template<typename component_type>
void scene::remove_component(entity_id id)
{
    if (m_entities[get_entity_index(id)].m_id != id)
    {
        return nullptr;
    }

    int component_id = get_component_id<component_type>();
    m_entities[get_entity_index(id)].m_mask.reset(component_id);
}
};
