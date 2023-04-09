#pragma once 

#include <atomic>

class OrangePiZero_WiringPi_PinMapping;

enum class enumPinMode : uint8_t {
    INPUT_MODE,
    OUTPUT_MODE,
    PWM_OUTPUT_MODE,
    GPIO_CLOCK_MODE
};

enum class enumPUDControl : uint8_t {
    OFF,
    DOWN,
    UP
};

class gpio_pin {
    uint8_t phyIndex = 0;
    uint8_t libIndex = 0;
    std::atomic<uintptr_t> masterObjectId = {0};

protected:
    gpio_pin() {};
    gpio_pin(
        const uint8_t &inPhyIndex,
        const uint8_t &inLibIndex
    );
    gpio_pin &operator=(const gpio_pin &&rhv);
public:
    void use(const uintptr_t &masterObjectId);
    void not_use(const uintptr_t &masterObjectId);
    virtual void set_pin_mode(const enumPinMode inPinMode) = 0;
    virtual void pull_up_dn_control(const enumPUDControl inPUDControl) = 0;
    virtual void digital_write(const bool inValue) = 0;
    virtual bool digital_read() = 0;
    uint8_t libIdx() { return libIndex; };
    uint8_t phyIdx() { return phyIndex; };
    virtual ~gpio_pin() {};
};

