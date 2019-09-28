/*
    Created by Yanir Harel, 28.9.2019
    ---------------------------------
    This module uses the torq direction.
*/

#pragma once

#include "hBridge.hpp"

class Torquer {
public:
    Torquer(void);
    ~Torquer(void);
    void set_dir_x (int x_dir);
    void set_dir_y (int y_dir);
    void set_dir_z (int z_dir);
    void reset_dir (void);
private:
    double direction [3]; // x, y, z
    hBridge* hBridges [3]; // x, y, z
    constexpr static int X { 0 }, Y = { 1 }, Z =  { 2 };
};