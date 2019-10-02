#include <iostream>
#include <exception>
#include <string>

using std::exception;

class GPIOException: public exception {
    const char* what() const throw();
};
