#include "gpio_pins_wiringPi.hpp"
#include <wiringPi.h>
#include <stdexcept>

void gpio_pin_wiringPi::set_pin_mode(const enumPinMode inPinMode)
{
    switch (inPinMode)
    {
    case enumPinMode::INPUT_MODE:
        pinMode(gpio_pin::libIdx(), INPUT);
        break;
    case enumPinMode::OUTPUT_MODE:
        pinMode (gpio_pin::libIdx(), OUTPUT);
        break;
    case enumPinMode::PWM_OUTPUT_MODE:
        pinMode (gpio_pin::libIdx(), PWM_OUTPUT);
        break;
    case enumPinMode::GPIO_CLOCK_MODE:
        pinMode (gpio_pin::libIdx(), GPIO_CLOCK);
        break;
    default:
        throw std::runtime_error("Not supported enumPinMode");
        break;
    }
}

void gpio_pin_wiringPi::pull_up_dn_control(const enumPUDControl inPUDControl)
{
    switch (inPUDControl) {
    case enumPUDControl::OFF:
        pullUpDnControl(gpio_pin::libIdx(), PUD_OFF);
        break;
    case enumPUDControl::DOWN:
        pullUpDnControl(gpio_pin::libIdx(), PUD_DOWN);
        break;
    case enumPUDControl::UP:
        pullUpDnControl(gpio_pin::libIdx(), PUD_UP);
        break;
    default:
        throw std::runtime_error("Not supported enumPUDControl mode");
        break;
    }
}

void gpio_pin_wiringPi::digital_write(const bool inValue)
{
    if (inValue) {
        digitalWrite(gpio_pin::libIdx(), HIGH);
    } else {
        digitalWrite(gpio_pin::libIdx(), LOW);
    }
}

bool gpio_pin_wiringPi::digital_read()
{
    if (digitalRead(gpio_pin::libIdx()) == HIGH){
        return true;
    }
    return false;
}

    