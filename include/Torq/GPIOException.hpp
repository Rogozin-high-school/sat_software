#include <iostream>
#include <exception>
#include <string>

using std::exception;

class GPIOException: public exception {
    virtual const char* what() const throw();
};
