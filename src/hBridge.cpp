#include "hBridge.hpp"

using std::string;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::exception;

hBridge::hBridge(string portNames[]) {
    for (int i = 0; i < 2; i++) {
        ports[i] = new GPIOClass(portNames[i]);
        if (!ports[i]->export_gpio()) {
            ports[i]->setdir_gpio("out");
        } else {
            throw GPIOException();
        }
    }
}

hBridge::~hBridge() {
    for (auto& port : ports) {
        port->unexport_gpio();
        delete port;
    }
}

void hBridge::setDirection(int dir) {
    switch (dir) {
    case 0: { // all gates are open
        for (auto& port : ports) {
            port->setval_gpio("0");
        }
    }break;
    case 1: { // all gates are closed except for directionPort1
        for (int i = 1; i < 2; i++) {
            ports[i]->setval_gpio("1");
        }
        ports[0]->setval_gpio("0"); // directionport1
    }break;
    case -1: { // all gates are closed except for directionPort2
        for (int i = 0; i < 2; i++) {
            if (i == 1) { // directionP.ort2
                ports[i]->setval_gpio("0");
            } else {
                ports[i]->setval_gpio("1");
            }
        }
    }break;
    }
}