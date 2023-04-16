#include "orangePiZeroWiringPi.hpp"

#include <wiringPi.h>
#include <stdexcept>
#include <iostream>

OrangePiZero_WiringPi_PinMapping *OrangePiZero_WiringPi_PinMapping::instance = nullptr;

OrangePiZero_WiringPi_PinMapping::OrangePiZero_WiringPi_PinMapping()
{
    if (wiringPiSetup() == -1) {
      throw std::runtime_error("Error when wiringPiSetup");
    }
    std::cout << "wiringPi for OrangePi inited" << std::endl;
    _PA10 = gpio_pin_wiringPi(26, 16);
    _PA13 = gpio_pin_wiringPi(24, 15);     _PA14 = gpio_pin_wiringPi(23, 14); 
    _PA02 = gpio_pin_wiringPi(22, 13);     _PA16 = gpio_pin_wiringPi(21, 12); 
                                           _PA15 = gpio_pin_wiringPi(19, 11);
    _PA18 = gpio_pin_wiringPi(18, 10);
    _PA19 = gpio_pin_wiringPi(16, 9);      _PA03 = gpio_pin_wiringPi(15, 8); 
                                           _PA00 = gpio_pin_wiringPi(13, 7);
    _PA07 = gpio_pin_wiringPi(12, 6);      _PA01 = gpio_pin_wiringPi(11, 5); 
    _PG07 = gpio_pin_wiringPi(10, 4);
    _PG06 = gpio_pin_wiringPi(8, 3);       _PA06 = gpio_pin_wiringPi(7, 2); 
                                           _PA11 = gpio_pin_wiringPi(5, 1);
                                           _PA12 = gpio_pin_wiringPi(3, 0);
}

OrangePiZero_WiringPi_PinMapping &OrangePiZero_WiringPi_PinMapping::get() {
    if (instance == nullptr) {
        instance = new OrangePiZero_WiringPi_PinMapping();
    }
    return *instance;
}

gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA10() { return _PA10; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA13() { return _PA13; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA02() { return _PA02; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA18() { return _PA18; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA19() { return _PA19; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA07() { return _PA07; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PG07() { return _PG07; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PG06() { return _PG06; }

gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA14() { return _PA14; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA16() { return _PA16; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA15() { return _PA15; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA03() { return _PA03; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA00() { return _PA00; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA01() { return _PA01; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA06() { return _PA06; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA11() { return _PA11; }
gpio_pin_wiringPi &OrangePiZero_WiringPi_PinMapping::PA12() { return _PA12; }

OrangePiZero_WiringPi_PinMapping::~OrangePiZero_WiringPi_PinMapping(){}
