#pragma once

#include "gpio_pins_wiringPi.hpp"


// naming of PinMapping classes classes for every platform and lib is based on following template
// <name of platform>_<name of Lib>_PinMapping

class OrangePiZero_WiringPi_PinMapping {
    gpio_pin_wiringPi _PA10;             /*gpio_pin_wiringPi _ground25;*/
    gpio_pin_wiringPi _PA13;             gpio_pin_wiringPi _PA14;
    gpio_pin_wiringPi _PA02;             gpio_pin_wiringPi _PA16;
    /*gpio_pin_wiringPi _ground20;*/     gpio_pin_wiringPi _PA15;
    gpio_pin_wiringPi _PA18;             /*gpio_pin_wiringPi _pwr3.3_17;*/
    gpio_pin_wiringPi _PA19;             gpio_pin_wiringPi _PA03;
    /*gpio_pin_wiringPi _ground14;*/     gpio_pin_wiringPi _PA00;
    gpio_pin_wiringPi _PA07;             gpio_pin_wiringPi _PA01;
    gpio_pin_wiringPi _PG07;             /*gpio_pin_wiringPi _ground09;*/
    gpio_pin_wiringPi _PG06;             gpio_pin_wiringPi _PA06;
    /*gpio_pin_wiringPi _ground06;*/     gpio_pin_wiringPi _PA11;
    /*gpio_pin_wiringPi _pwr5_4;*/       gpio_pin_wiringPi _PA12;
    /*gpio_pin_wiringPi _pwr5_2;*/       /*gpio_pin_wiringPi _pwr3.3_1;*/
    static OrangePiZero_WiringPi_PinMapping *instance;

    OrangePiZero_WiringPi_PinMapping();
public:
    static OrangePiZero_WiringPi_PinMapping &get();
    gpio_pin_wiringPi &PA10();
    gpio_pin_wiringPi &PA13();
    gpio_pin_wiringPi &PA02();
    gpio_pin_wiringPi &PA18();
    gpio_pin_wiringPi &PA19();
    gpio_pin_wiringPi &PA07();
    gpio_pin_wiringPi &PG07();
    gpio_pin_wiringPi &PG06();

    gpio_pin_wiringPi &PA14();
    gpio_pin_wiringPi &PA16();
    gpio_pin_wiringPi &PA15();
    gpio_pin_wiringPi &PA03();
    gpio_pin_wiringPi &PA00();
    gpio_pin_wiringPi &PA01();
    gpio_pin_wiringPi &PA06();
    gpio_pin_wiringPi &PA11();
    gpio_pin_wiringPi &PA12();
    ~OrangePiZero_WiringPi_PinMapping();
};
