#ifdef RASPBERRY_PI

#include <raspberry_pi/gpio.hpp>
#include <string>
#include <fstream>
#include <array>

namespace RaspberryPi {
    void GPIO::initialize(PinNumber pinNumber = 4) {
        _pinNumber = pinNumber;
    }

    template<class T>
    inline void write_to_file(const std::string& path, T value, const std::string&& errMsg) {
        std::ofstream file(path);
        if (file.fail()) {
            throw std::runtime_error(errMsg);
        }
        file << value;
        file.close();
    }

    void GPIO::export_gpio() {
        constexpr auto path = "/sys/class/gpio/export";
        const std::string strPinNumber = std::to_string(pinNumber);
        write_to_file(path, strPinNumber, 
            "Unable to export GPIO pin #" + strPinNumber + "!");
    }

    void GPIO::unexport_gpio() {
        constexpr auto path = "/sys/class/gpio/unexport";
        const std::string strPinNumber = std::to_string(pinNumber);
        write_to_file(path, strPinNumber, 
            "Unable to unexport GPIO pin #" + strPinNumber + "!");
    }

    void GPIO::set_direction(GPIODirection direction) {
        const std::string strPinNumber = std::to_string(pinNumber);
        const auto path = "/sys/class/gpio/gpio" + strPinNumber + "/direction";
        write_to_file(path, direction == GPIODirection::IN ? "in" : "out", 
            "Unable to set direction on GPIO pin #" + strPinNumber + "!");
    }

    void GPIO::set_value(GPIOValue value) {
        const std::string strPinNumber = std::to_string(pinNumber);
        const auto path = "/sys/class/gpio/gpio" + strPinNumber + "/value";
        write_to_file(path, std::to_string(value),
            "Unable to set value on GPIO pin #" + strPinNumber + "!");
    }
}

#endif // RASPBERRY_PI