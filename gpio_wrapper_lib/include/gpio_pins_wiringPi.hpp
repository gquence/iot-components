#pragma once 

#include "gpio_pins.hpp"
#include <atomic>

class OrangePiZero_WiringPi_PinMapping;

class gpio_pin_wiringPi : public gpio_pin {

protected:  
    gpio_pin_wiringPi(): gpio_pin() {};
    gpio_pin_wiringPi(
        const uint8_t &inPhyIndex,
        const uint8_t &inLibIndex
    ) : gpio_pin(inPhyIndex, inLibIndex) {};
    gpio_pin_wiringPi &operator=(const gpio_pin_wiringPi &&rhv){
        return *this;
    };
public:
    void set_pin_mode(const enumPinMode inPinMode);
    void pull_up_dn_control(const enumPUDControl inPUDControl);
    void digital_write(const bool inValue);
    bool digital_read();

    ~gpio_pin_wiringPi() {};
    friend class OrangePiZero_WiringPi_PinMapping;
};

