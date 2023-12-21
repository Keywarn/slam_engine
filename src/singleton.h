#pragma once
#include <mutex>
#include <iostream>

template <typename derived_class>
class singleton
{
public:
    singleton()
    {
        s_instance = static_cast<derived_class*>(this);
    }
    ~singleton()
    {
        s_instance = nullptr;
    }

    // Can't clone
    singleton(singleton& other) = delete;
    // Can't assign
    void operator=(const singleton&) = delete;

    static derived_class* get_instance()
    {
        std::lock_guard<std::mutex> lock(s_mutex);
        
        if (s_instance == nullptr)
        {
            std::cout << "ERROR::SINGLETON::ACCESSING UNINITIALISED SINGLETON"<< std::endl;
            __debugbreak();
        }

        return s_instance;
    }

protected:
    inline static derived_class* s_instance;
    inline static std::mutex s_mutex;
};

