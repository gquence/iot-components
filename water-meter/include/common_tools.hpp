#pragma once

#include <chrono>

int64_t steadyTimeInMsSeconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
