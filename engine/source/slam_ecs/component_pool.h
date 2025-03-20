#pragma once

namespace slam
{
extern int MAX_ENTITIES;
class component_pool
{
public:
    component_pool(size_t element_size)
    {
        m_element_size = element_size;
        m_data = new char[m_element_size * MAX_ENTITIES];
    }

    ~component_pool()
    {
        delete[] m_data;
    }

    inline void* get(size_t index)
    {
        return m_data + index * m_element_size;
    }

private:
    char* m_data{ nullptr };
    size_t m_element_size{ 0 };
};
};
