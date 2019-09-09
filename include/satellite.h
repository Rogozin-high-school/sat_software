/*
    Created by Maor Gershman, 6.9.2019
    ---
    This file will contain the satellite class.
*/

#pragma once

namespace SatelliteSoftware {
    class Satellite {
    private:
        int propExitCode;
    public:
        const int& exitCode;

        Satellite();
        ~Satellite();
    };
}