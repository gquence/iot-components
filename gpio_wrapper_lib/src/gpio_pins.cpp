#include "gpio_pins.hpp"

#include <utility>

#define FMT_ENFORCE_COMPILE_STRING
#include <fmt/format.h>

gpio_pin::gpio_pin(
    const uint8_t &inPhyIndex,
    const uint8_t &inLibIndex
) :  phyIndex(inPhyIndex), libIndex(inLibIndex)
{}


void gpio_pin::use(const uintptr_t &inMasterObjectId) {
    static uintptr_t null_ptr = 0;

    if (!masterObjectId.compare_exchange_strong(null_ptr, inMasterObjectId)) {
        throw std::runtime_error(fmt::format(FMT_STRING("Pin #{} with libId{} is already in use by '{}' object"), phyIndex, libIndex, masterObjectId));
    }
}

void gpio_pin::not_use(const uintptr_t &inMasterObjectId){
    if (masterObjectId == inMasterObjectId){
        throw std::runtime_error(fmt::format(FMT_STRING("Pin #{} with libId{} is in use by '{}' object"), phyIndex, libIndex, masterObjectId));
    }
}
