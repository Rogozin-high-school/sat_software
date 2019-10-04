#include "../include/Torq/Torq.hpp"

Torquer::Torquer () {
    string pins[3][2] = { { "20", "26" }, { "16", "19" }, { "23", "22" } };
    for (int i = 0; i < 3; i++) {
        this->directions[i] = 0;
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
    this->directions[this->X] = x_dir;
    this->hBridges[this->X]->setDirection (x_dir);
}

void Torquer::set_dir_y (int y_dir) {
    if (y_dir && y_dir != 1 && y_dir != -1) return;
    this->directions[this->Y] = y_dir;
    this->hBridges[this->Y]->setDirection (y_dir);
}

void Torquer::set_dir_z (int z_dir) {
    if (z_dir && z_dir != 1 && z_dir != -1) return;
    this->directions[this->Z] = z_dir;
    this->hBridges[this->Z]->setDirection (z_dir);
}

void Torquer::reset (void) {
    for (auto& i : this->directions) {
        i = 0;
    }
    for (auto& i : this->hBridges) {
        i->setDirection(0);
    }
}
