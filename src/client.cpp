/*
    Created by Maor Gershman, 25.8.2019
*/

#include "../include/logger.h"
#include "../include/client.h"

namespace Satellite {
    Client::Client() {
        Logger::log("Created the client!");
    }

    bool Client::connect(std::string address, int port) const {
        Logger::log("Attempting connection to " + address + ":" + std::to_string(port) + "...");
        // TODO: Actually connect to the server...
        return false;
    }
}