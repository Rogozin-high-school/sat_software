/*
    Created by Maor Gershman, 25.8.2019
    ---
    This is the entry point of the satellite app.
    This file should be as short and precise as possible.
*/

#include "../include/logger.h"
#include "../include/client.h"

int main(void) {
    Satellite::Logger::log("Starting the satellite!");

    Satellite::Client client;
    if (!client.connect()) {
        Satellite::Logger::log("Connection has failed!");
        return 1;
    }
    Satellite::Logger::log("Connected!");
    
    return 0;
}
