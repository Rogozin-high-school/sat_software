/*
    Created by Maor Gershman, 25.8.2019
    ---
    This is the entry point of the satellite app.
    This file should be as short and precise as possible.
*/

#include <satellite.hpp>

int main(void) {
    Satellite satellite;

    try {
        satellite.run();
    } catch (...) {
        // Let's hope we won't get here!
        return 1;
    }
    
    // Or here too!
    return 0;
}
