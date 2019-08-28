/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will print messages to the terminal, 
    only if in debugging mode.
*/

#pragma once
#include "main.h"
#include <iostream>
#include <time.h>

namespace Satellite {
    class Logger {
    private:
        static inline std::string current_time_string() {
            char buffer[32];
            time_t t;
            time(&t);
            tm *tmStruct = localtime(&t);
            strftime(buffer, sizeof(buffer), "%a, %d %b %Y, %H:%M:%S", tmStruct);
            return buffer;
        }
    public:
        template<class T>
        static inline void log(T t) {
            if /*constexpr*/ (Debug) {
                std::cout << "[" << current_time_string() << "] ";
                std::cout << "[Debug] ";
                std::cout << t << std::endl;
            }
        }
    };
}