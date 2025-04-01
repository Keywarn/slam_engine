#pragma once

#include "scene.h"

namespace slam
{
template<typename... component_types>
class scene_view
{
public:
    scene_view(scene& scene);

    struct iterator;

    const iterator begin() const;
    const iterator end() const;

    //const iterator begin() const;
    //const iterator end() const;

private:
    scene* m_scene = nullptr;
    bool m_all = false;
    component_mask m_mask;
};

template<typename... component_types>
struct scene_view<component_types...>::iterator
{
        iterator(scene * scene, entity_index index, component_mask mask, bool all)
            : m_scene(scene), m_index(index), m_mask(component_mask), m_all(all)
        {
        }

        bool is_valid_index()
        {
            return is_entity_valid(m_scene->entities[m_index].m_id) &&
                (m_all || m_mask == (m_mask & m_scene->m_entities[m_index].m_mask));
        }

        entity_id operator*()
        {
            return m_scene->m_entities[m_index].m_id;
        }
        bool operator==(const iterator & other) const
        {
            return m_index == other.m_index || m_index == m_scene->m_entities.size();
        }
        bool operator!=(const iterator & other) const
        {
            return m_index != other.m_index && m_index != m_scene->m_entities.size();
        }
        iterator & operator++()
        {
            do
            {
                m_index++;
            } while (m_index < m_scene->m_entities.size() && !is_valid_index());
            return *this;
        }

        entity_index m_index;
        scene* m_scene;
        component_mask m_mask;
        bool m_all{ false };
};

};