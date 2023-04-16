#include "water_meter.hpp"

#include "common_tools.hpp"

#include <memory>
#include <future>
#include <iostream>

#define FMT_ENFORCE_COMPILE_STRING
#include <fmt/format.h>

impulse_water_meter::impulse_water_meter(
    const std::string &in_id,
    gpio_pin *in_Input_Pin,
    gpio_pin *in_Output_Pin,
    uint64_t in_start_liter_amount
) : id(in_id),
    Input_Pin(in_Input_Pin),
    Output_Pin(in_Output_Pin),
    start_liter_amount(in_start_liter_amount),
    current_liter_amount(in_start_liter_amount)
{
    Input_Pin->use(reinterpret_cast<uintptr_t>(this));
    Output_Pin->use(reinterpret_cast<uintptr_t>(this));


    Input_Pin->set_pin_mode(enumPinMode::INPUT_MODE);
    Output_Pin->set_pin_mode(enumPinMode::OUTPUT_MODE);
    Input_Pin->pull_up_dn_control(enumPUDControl::DOWN);
    Output_Pin->digital_write(true);
    printf("impulse_water_meter connected Input_Pin: %d\n", Input_Pin->libIdx());
    printf("impulse_water_meter connected Output_Pin: %d\n", Output_Pin->libIdx());
    initPeriodicHandler();
}

void impulse_water_meter::initPeriodicHandler()
{
    std::shared_ptr<std::promise<bool>> isRunning = std::make_shared<std::promise<bool>>();
    auto isConnOk = isRunning->get_future();

    // run connection thread
    m_periodic_thread = std::thread(
        [this](std::shared_ptr<std::promise<bool>> barrier) {
            try {
                // set thread started flag
                barrier->set_value(true);

                while (! m_stop ) {
                    periodicHandler();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            } catch (const std::exception& e) {
                std::cerr << fmt::format(FMT_STRING("impulse_water_meter {} periodic control thread exception due to: {}"), fmt::ptr(this), e.what());
                return;
            }

            std::cerr << fmt::format(FMT_STRING("impulse_water_meter {} periodic control thread has stopped"), fmt::ptr(this));

            return;
        },
        isRunning
    );

    // wait 5 sec for error status
    if (auto result = isConnOk.wait_for(std::chrono::seconds(5)); result != std::future_status::ready) {
        deinitHandlers();
        throw std::runtime_error(fmt::format(FMT_STRING( "Can't init impulse_water_meter {}: Periodic thread has not started"), fmt::ptr(this)));
    }

    return;
}


void impulse_water_meter::updateCurrentMeterValue()
{
    bool new_signal_status = Input_Pin->digital_read();

    if (m_current_signal_status != new_signal_status) {
        if (new_signal_status) {
            current_liter_amount += 10;
        }
        m_current_signal_status = new_signal_status;
    }
    return ;
}

void impulse_water_meter::sendCurrentMeterValueToAllSubscribers()
{
    updateValue valueToSend;
    valueToSend.id = id;
    valueToSend.value.resize(8);
    *((uint64_t *)(valueToSend.value.data())) = current_liter_amount;
    for (auto &sub: subscribers) {
        sub->update(valueToSend);
    }
}


void impulse_water_meter::periodicHandler()
{
    lockG lock(m_mutex);
    uint64_t oldMeterValue = current_liter_amount;
    updateCurrentMeterValue();
    if (oldMeterValue != current_liter_amount) {
        sendCurrentMeterValueToAllSubscribers();
    }    
}

void impulse_water_meter::deinitHandlers()
{
    m_stop = true;
    if (m_periodic_thread.joinable()) {
        m_periodic_thread.join();
    }
}

impulse_water_meter::~impulse_water_meter()
{
    deinitHandlers();

    Input_Pin->pull_up_dn_control(enumPUDControl::OFF);
    Output_Pin->digital_write(true);
    Input_Pin->not_use(reinterpret_cast<uintptr_t>(this));
    Output_Pin->not_use(reinterpret_cast<uintptr_t>(this));
}
