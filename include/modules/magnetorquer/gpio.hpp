#pragma once

#include <string>
#include <stdint.h>

namespace Modules {
    class GPIO {
    public:
        enum class Pin          : uint8_t {};

        enum class Direction    : uint8_t { IN, OUT };

        enum class Value        : uint8_t { OPEN = 0, CLOSED = 1 };

        const GPIO::Pin& pin = _pin;

        void initialize(GPIO::Pin pin); 
        void export_gpio();
        void unexport_gpio();
        void set_direction(GPIO::Direction direction);
        void set_value(GPIO::Value value);
    private:
        GPIO::Pin _pin;
        std::string pinStr;
    };
}