#include "GPIOException.hpp"

const char* GPIOException::what() const throw() {
    return "error opening gpio!";
}