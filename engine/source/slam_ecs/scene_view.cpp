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
};
