#include <modules/magnetorquer/gpio.hpp>
#include <properties.hpp>
#include <logger.hpp>
#include <fstream>

namespace Modules {
    void GPIO::initialize(GPIO::Pin pin) {
        _pin = pin;

        pinStr = std::to_string(int(pin));
        Logger::verbose<LogPrefix::GPIO>("Initialized GPIO pin #" + pinStr + "!");
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
        const std::string pinExportPath = Properties::get_string("pin_export_path");

        Logger::verbose<LogPrefix::GPIO>("Exporting pin #" + pinStr + " to \"" + pinExportPath + "\"!");
#ifdef RASPBERRY_PI
        write_to_file(pinExportPath, pinStr, "Unable to export pin #" + pinStr + "!");
#endif // RASPBERRY_PI
    }

    void GPIO::unexport_gpio() {
        const std::string pinUnexportPath = Properties::get_string("pin_unexport_path");

        Logger::verbose<LogPrefix::GPIO>("Unexporting pin #" + pinStr + " to \"" + pinUnexportPath + "\"!");
#ifdef RASPBERRY_PI
        write_to_file(pinUnexportPath, pinStr, "Unable to unexport pin #" + pinStr + "!");
#endif // RASPBERRY_PI
    }

    inline void replace_char_with_string(std::string& str, char c, std::string replacement) {
        int position;
        while ((position = str.find(c)) != std::string::npos) {
            str.replace(position, 1, replacement);
        }
    }

    void GPIO::set_direction(GPIO::Direction direction) {
        std::string directionStr = direction == GPIO::Direction::IN ? "in" : "out";

        std::string pinDirectionPath = Properties::get_string("pin_direction_path");
        replace_char_with_string(pinDirectionPath, '#', pinStr);

        Logger::verbose<LogPrefix::GPIO>("Setting pin #" + pinStr + " direction at \"" + pinDirectionPath + "\" to \"" + directionStr + "\"!");
#ifdef RASPBERRY_PI
        write_to_file(pinDirectionPath, directionStr, "Unable to set direction on pin #" + pinStr + "!");
#endif // RASPBERRY_PI
    }

    void GPIO::set_value(GPIO::Value value) {
        std::string valueStr = std::to_string(int(value));

        std::string pinValuePath = Properties::get_string("pin_value_path");
        replace_char_with_string(pinValuePath, '#', pinStr);

        Logger::verbose<LogPrefix::GPIO>("Setting pin #" + pinStr + " value at \"" + pinValuePath + "\" to \"" + valueStr + "\"!");
#ifdef RASPBERRY_PI
        write_to_file(pinValuePath, valueStr, "Unable to set value on pin #" + pinStr + "!");
#endif // RASPBERRY_PI
    }
}