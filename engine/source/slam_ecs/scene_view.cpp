#include "scene_view.h"

namespace slam
{
template<typename... component_types>
scene_view<component_types...>::scene_view(scene& scene)
    : m_scene(&scene)
{
    if (sizeof...(component_types) == 0)
    {
        m_all = true;
    }
    else
    {
        int component_ids[] = { 0, get_component_id<component_types>()... };
        for (int i = 1; i < (sizeof...(component_types) + 1); i++)
        {
            m_mask.set(component_ids[i]);
        }
    }
}

template<typename... component_types>
const typename scene_view<component_types...>::iterator scene_view<component_types...>::begin() const
{
    int index = 0;
    while (index < m_scene->m_entities.size() &&
        (m_mask != (m_mask & m_scene->m_entities[index].m_mask)
            || !is_entity_valid(m_scene->m_entities[index].m_id)))
    {
        index++;
    }
    return iterator(m_scene, index, m_mask, m_all);
}

template<typename... component_types>
const typename scene_view<component_types...>::iterator scene_view<component_types...>::end() const
{
    return iterator(m_scene, entity_index(m_scene->m_entities.size()), m_mask, m_all);
}

};
