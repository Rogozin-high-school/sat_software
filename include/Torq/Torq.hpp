#pragma once

#include "hBridge.hpp"

class Torquer {
public:
    Torquer(void);
    ~Torquer(void);
    void set_dir_x (int x_dir);
    void set_dir_y (int y_dir);
    void set_dir_z (int z_dir);
    void reset (void);
    int directions[3];
private:
    hBridge* hBridges [3]; // x, y, z
    constexpr static int X { 0 }, Y = { 1 }, Z =  { 2 };
};
