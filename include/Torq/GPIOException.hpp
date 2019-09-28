/*
    Created by Yanir Harel, 28.9.2019
    ---------------------------------
    Custom Exception to alert of gpio opening errors
*/

#pragma once

#include <iostream>
#include <exception>
#include <string>

using std::exception;

class GPIOException: public exception {
    virtual const char* what() const throw();
};
