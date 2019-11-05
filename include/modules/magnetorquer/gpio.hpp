#pragma once

namespace Modules::SubModules {
    class GPIO {
    public:
        enum class Pin : unsigned char {};

        enum class Direction : bool { IN, OUT };

        enum class Value : bool { 
            CLOSED = true, 
            OPEN = false 
        };

        const GPIO::Pin& pin = _pin;

        void initialize(GPIO::Pin pin); 
        void export_gpio();
        void unexport_gpio();
        void set_direction(GPIO::Direction direction);
        void set_value(GPIO::Value value);
    private:
        GPIO::Pin _pin;
    };
}