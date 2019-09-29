/*
    Created by Yanir Harel, 28.9.2019
    ---------------------------------
    Custom Exception to alert of gpio opening errors
*/

#include "../include/Torq/GPIOException.hpp"

const char* GPIOException::what() const throw() {
    return "error opening gpio!";
}