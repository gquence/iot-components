#include "orangePiZeroWiringPi.hpp"
#include "water_meter.hpp"

#include <vector>
#include <queue>
#include <iostream>
#include <future>

#define FMT_ENFORCE_COMPILE_STRING
#include <fmt/format.h>

class outLogger : public objectIface
{
    std::mutex m_mutex;
    std::queue<updateValue> m_received_data;
    std::atomic<bool> m_stop{false};
    std::thread m_periodic_thread;
public:
    outLogger() {
        std::shared_ptr<std::promise<bool>> isRunning = std::make_shared<std::promise<bool>>();
        auto isConnOk = isRunning->get_future();

        // run connection thread
        m_periodic_thread = std::thread(
            [this](std::shared_ptr<std::promise<bool>> barrier) {
                try {
                    // set thread started flag
                    barrier->set_value(true);

                    while (! m_stop ) {
                        print();
                        std::this_thread::sleep_for(std::chrono::milliseconds(400));
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
            throw std::runtime_error(fmt::format(FMT_STRING( "Can't init impulse_water_meter {}: Periodic thread has not started"), fmt::ptr(this)));
        }

        return;
    }
    void update(updateValue &value)
    {
        lockG lock(m_mutex);
        m_received_data.emplace(value);
    }
    void print()
    {
        std::queue<updateValue> receivedData;
        {
            lockG lock(m_mutex);
            receivedData = m_received_data;
            while (!m_received_data.empty()) {
                m_received_data.pop();
            }
        }
        while (!receivedData.empty())
        {
            auto &data_elem = receivedData.front();
            if (data_elem.value.size() != 8) {
                throw std::runtime_error("Are you dolboy-yob?");
            }
            uint64_t value = *((uint64_t *)data_elem.value.data());
            std::cout << "id: " << data_elem.id << " value: " << value << std::endl; 
            receivedData.pop();
        }
    }
    ~outLogger(){
        m_stop = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    };
};

int main()
{
    std::vector<std::shared_ptr<impulse_water_meter>> meters;
    meters.reserve(2);
    {
        std::string id = "cold_water";
        uint64_t start_liter_amount = 10;
        meters.emplace_back(
            std::make_shared<impulse_water_meter>(
                id,
                &OrangePiZero_WiringPi_PinMapping::get().PA14(),
                &OrangePiZero_WiringPi_PinMapping::get().PA13(),
                start_liter_amount
            )
        );
    }
    {
        std::string id = "warm_water";
        uint64_t start_liter_amount = 10;
        meters.emplace_back(
            std::make_shared<impulse_water_meter>(
                id,
                &OrangePiZero_WiringPi_PinMapping::get().PA16(),
                &OrangePiZero_WiringPi_PinMapping::get().PA02(),
                start_liter_amount
            )
        );
    }
    std::shared_ptr<outLogger> logger = std::make_shared<outLogger>();
    meters[0]->registerSubscriber(logger);
    meters[1]->registerSubscriber(logger);

    while (1) {
    }

    return 0;
}