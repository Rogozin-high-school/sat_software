/*
    Created by Maor Gershman, 25.8.2019
    Updated and Upgraded by Yanir Harel, 28.9.2019
    ---
    This is the entry point of the satellite app.
    This file should be as short and precise as possible.
*/

#include <stdio.h>
#include "../include/satellite.h"

int main(void) {
    SatelliteSoftware::Satellite satellite;
    try {
        satellite.run();
    } catch (...) {
        puts("exception accured");
        return 1;
    }
    return 0;
}
