#pragma once

#include <bitset>
#include <vector>

#include "component_pool.h"

namespace slam
{

typedef unsigned long long entity_id;
const int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> component_mask;

struct entity_data
{
    entity_id m_id;
    component_mask m_mask;
};

class scene
{
public:
    entity_id new_entity();

    template<typename component_type>
    void assign_component(entity_id id);

private:
    std::vector<entity_data> m_entities;
    std::vector<component_pool> component_pools;
};


static int s_component_counter = 0;
template <class T>
int get_component_id()
{
    static int id = s_component_counter++;
    return id;
}

};