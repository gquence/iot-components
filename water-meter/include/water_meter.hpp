#pragma once

#include "iface_meter.hpp"
#include "gpio_pins.hpp"

#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

using lockG = std::lock_guard<std::mutex>;


struct updateValue
{
    std::string id;
    std::vector<uint8_t> value;
};

class objectIface 
{
public:
    virtual void update(updateValue &) {};
    virtual ~objectIface() {};
};


class impulse_water_meter : public iface_meter
{
private:
    std::string id;
    const uint64_t start_liter_amount;   // we add only 10 liters at a time
    uint64_t current_liter_amount; //
    std::mutex m_mutex;

    gpio_pin *Input_Pin;
    gpio_pin *Output_Pin;

    std::vector<std::shared_ptr<objectIface>> subscribers;

    std::atomic<bool> m_stop{false};
    std::thread m_periodic_thread;
    bool m_current_signal_status{false}; // ON|OFF

    void updateCurrentMeterValue();
    void sendCurrentMeterValueToAllSubscribers();

    void initPeriodicHandler();
    void deinitHandlers();
    void periodicHandler();
public:
    impulse_water_meter() = delete;
    impulse_water_meter(
        const std::string &in_id,
        gpio_pin *in_Input_Pin,
        gpio_pin *in_Output_Pin,
        uint64_t in_start_liter_amount = 0
    );
    void registerSubscriber(std::shared_ptr<objectIface> new_obj)
    {
        lockG lock(m_mutex);
        subscribers.emplace_back(new_obj);
    };
    void unRegisterSubscriber(std::shared_ptr<objectIface> obj)
    {
        lockG lock(m_mutex);
        auto it = std::find(subscribers.begin(), subscribers.end(), obj);
        subscribers.erase(it);
    };
    ~impulse_water_meter();
};
