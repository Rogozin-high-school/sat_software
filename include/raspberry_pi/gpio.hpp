#ifdef RASPBERRY_PI

#pragma once

namespace RaspberryPi {
    using PinNumber = unsigned char;
    using GPIOValue = bool;
    
    enum class GPIODirection : bool {
        IN, OUT
    };

    class GPIO {
    public:
        const PinNumber& pinNumber = _pinNumber;

        void initialize(PinNumber pinNumber); 

        void export_gpio();

        void unexport_gpio();

        void set_direction(GPIODirection direction);
        
        void set_value(GPIOValue value);
    private:
        PinNumber _pinNumber;
    };
}

#endif // RASPBERRY_PI