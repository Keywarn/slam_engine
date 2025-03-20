#pragma once

namespace slam
{

class component 
{

};


static int s_component_counter = 0;
template <class T>
int get_component_id()
{
    static int id = s_component_counter++;
    return id;
}

};
