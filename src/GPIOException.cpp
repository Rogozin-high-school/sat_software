#include "GPIOException.hpp"

virtual const char* GPIOException::what() const throw() {
    return "error opening gpio!";
}