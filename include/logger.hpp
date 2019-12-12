#pragma once

#ifdef LOGGING
#include <iostream>
#endif // LOGGING

static inline struct
{ // Wrapper for std::cout, doesn't support stuff like std::hex or std::endl
    template<class T>
    auto& operator<<(T&& t)
    {
#ifdef LOGGING
        std::cout << t;
#endif // LOGGING
        return *this;
    }
} log;