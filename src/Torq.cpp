/*
    Created by Yanir Harel, 28.9.2019
    ---------------------------------
    This module uses the torq direction.
*/

#include "Torq.hpp"

Torquer::Torquer () {
    string pins[3][2] = { { "20", "26" }, { "16", "19" }, { "23", "22" } };
    for (int i = 0; i < 3; i++) {
        this->direction[i] = 0;
        this->hBridges[i] = new hBridge(pins[i]);
    }
}

Torquer::~Torquer () {
    for (int i = 0; i < 3; i++) {
        delete this->hBridges[i];
    }
}

void Torquer::set_dir_x (int x_dir) {
    if (x_dir && x_dir != 1 && x_dir != -1) return;
    this->direction[this->X] = x_dir;
    this->hBridges[this->X]->setDirection (x_dir);
}

void Torquer::set_dir_y (int y_dir) {
    if (y_dir && y_dir != 1 && y_dir != -1) return;
    this->direction[this->Y] = y_dir;
    this->hBridges[this->Y]->setDirection (y_dir);
}

void Torquer::set_dir_z (int z_dir) {
    if (z_dir && z_dir != 1 && z_dir != -1) return;
    this->direction[this->Z] = z_dir;
    this->hBridges[this->Z]->setDirection (z_dir);
}


void Torquer::reset_dir () { // close all hbridge ports and stop the torq
    for (int i = 0; i < 3; i++) {
        this->direction[i] = 0;
        this->hBridges[i]->setDirection (0);
    }
}