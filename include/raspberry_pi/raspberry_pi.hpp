#ifdef RASPBERRY_PI

#pragma once

#include <wiringPi.h>

namespace RaspberryPi {
    static inline void initialize() {
        wiringPiSetup();
    }
}

#endif // RASPBERRY_PI