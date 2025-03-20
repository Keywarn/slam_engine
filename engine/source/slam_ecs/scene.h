#pragma once

#include <bitset>
#include <vector>

#include "component_pool.h"

namespace slam
{

typedef unsigned int entity_index;
typedef unsigned int entity_version;
typedef unsigned long long entity_id; // index first 32 bits, version last 32
const int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> component_mask;

inline entity_id create_entity_id(entity_index index, entity_version version)
{
    return ((entity_id)index << 32) | ((entity_id)version);
}
inline entity_index get_entity_index(entity_id id)
{
    return id >> 32;
}
inline entity_version get_entity_version(entity_id id)
{
    return (entity_version)id;
}
inline bool is_entity_valid(entity_id id)
{
    return (id >> 32) != entity_index(-1);
}

#define INVALID_ENTITY CreateEntityId(EntityIndex(-1), 0)

struct entity_data
{
    entity_id m_id;
    component_mask m_mask;
};

class scene
{
public:
    entity_id new_entity();
    void destroy_entity(entity_id id);

    template<typename component_type>
    component_type* assign_component(entity_id id);

    template<typename component_type>
    component_type* get_component(entity_id id);

    template<typename component_type>
    void remove_component(entity_id id);

private:
    std::vector<entity_data> m_entities;
    std::vector<entity_index> m_free_entities;
    std::vector<component_pool> m_component_pools;
};


static int s_component_counter = 0;
template <class T>
int get_component_id()
{
    static int id = s_component_counter++;
    return id;
}

};