/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will handle the communication with the server.
*/

#pragma once
#include "main.h"

namespace Satellite {
    class Client {
    public:
        Client();
        bool connect(std::string address = Address, int port = Port) const;
    };
}