#include <satellite.hpp>

int main(void) {
    Satellite satellite;

    try {
        satellite.initialize();
        satellite.run();
    } catch (...) {
        // Let's hope we won't get here!
        try {
            satellite.cleanup();
        } catch (...) {
            // There's nothing you can do, since the satellite has already failed :(
        }
    }
    
    return 1;
}
