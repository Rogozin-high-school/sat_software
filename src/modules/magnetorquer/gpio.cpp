#include <modules/magnetorquer/gpio.hpp>
#include <logger.hpp>
#include <fstream>

namespace Modules::SubModules {
    void GPIO::initialize(GPIO::Pin pin = static_cast<GPIO::Pin>(4)) {
        _pin = pin;
        Logger::verbose<LogPrefix::MAGNETORQUER>("Initialized GPIO pin #" + std::to_string((int)pin) + "!");
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
        const std::string strPin = std::to_string((int)pin);
        
        Logger::verbose<LogPrefix::MAGNETORQUER>("Exporting GPIO pin #" + strPin + "!");
#ifdef RASPBERRY_PI
        constexpr auto path = "/sys/class/gpio/export";
        write_to_file(path, strPin, "Unable to export GPIO pin #" + strPin + "!");
#endif // RASPBERRY_PI
    }

    void GPIO::unexport_gpio() {
        const std::string strPin = std::to_string((int)pin);

        Logger::verbose<LogPrefix::MAGNETORQUER>("Unexporting GPIO pin #" + strPin + "!");
#ifdef RASPBERRY_PI
        constexpr auto path = "/sys/class/gpio/unexport";
        write_to_file(path, strPin, "Unable to unexport GPIO pin #" + strPin + "!");
#endif // RASPBERRY_PI
    }

    void GPIO::set_direction(GPIO::Direction direction) {
        const std::string strPin = std::to_string((int)pin);
        const std::string strDirection = direction == GPIO::Direction::IN ? "in" : "out";

        Logger::verbose<LogPrefix::MAGNETORQUER>("Setting GPIO pin #" + strPin + " direction to " + strDirection + "!");
#ifdef RASPBERRY_PI
        const auto path = "/sys/class/gpio/gpio" + strPin + "/direction";
        write_to_file(path, strDirection, "Unable to set direction on GPIO pin #" + strPin + "!");
#endif // RASPBERRY_PI
    }

    void GPIO::set_value(GPIO::Value value) {
        const std::string strPin = std::to_string((int)pin);
        const std::string strValue = std::to_string((int)value);

        Logger::verbose<LogPrefix::MAGNETORQUER>("Setting GPIO pin #" + strPin + " value to " + strValue + "!");
#ifdef RASPBERRY_PI
        const auto path = "/sys/class/gpio/gpio" + strPin + "/value";
        write_to_file(path, strValue, "Unable to set value on GPIO pin #" + strPin + "!");
#endif // RASPBERRY_PI
    }
}