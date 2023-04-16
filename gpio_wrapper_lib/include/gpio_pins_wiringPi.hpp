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
        phyIndex = rhv.phyIndex;
        libIndex = rhv.libIndex;
        return *this;
    };
public:
    virtual void set_pin_mode(const enumPinMode inPinMode);
    virtual void pull_up_dn_control(const enumPUDControl inPUDControl);
    virtual void digital_write(const bool inValue);
    virtual bool digital_read();

    ~gpio_pin_wiringPi() {};
    friend class OrangePiZero_WiringPi_PinMapping;
};

