/*
    Created by Maor Gershman, 6.9.2019
    Updated and Upgraded by Yanir Harel, 28.9.2019
    ---
    This file will contain the satellite class.
*/

#pragma once

namespace SatelliteSoftware {
    struct Satellite {
        Satellite();
        ~Satellite();

        void run() const;
    };
}