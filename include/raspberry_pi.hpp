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
    static inline void cleanup() {
#ifdef RASPBERRY_PI
        // TODO: cleanups
#endif // RASPBERRY_PI
    }
}