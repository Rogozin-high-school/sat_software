/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will handle the communication with the server.
*/

#pragma once
#include "main.h"
#include <arpa/inet.h>
#include <string>

namespace Satellite {
    class Client {
    private:
        std::string address;
        int port;

        sockaddr_in socketAddress;
        int socketHandle = -1;

        bool lastOperationSuccessful;

        void create_socket();
        void attempt_connection();
    public:
        Client(std::string address = Address, int port = Port);
        ~Client();
        bool success() const;
        bool failure() const;
    };
}