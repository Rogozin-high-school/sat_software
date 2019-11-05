#pragma once

#ifdef RASPBERRY_PI
#include <wiringPi.h>
#endif // RASPBERRY_PI

namespace RaspberryPi {
    static inline void initialize() {
#ifdef RASPBERRY_PI
        wiringPiSetup();
#endif // RASPBERRY_PI
    }
}
