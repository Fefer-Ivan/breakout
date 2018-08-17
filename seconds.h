#pragma once
#include <ctime>
#include <ratio>
#include <chrono>

namespace breakout {

using namespace std::chrono_literals;
using Seconds = std::chrono::duration<double, std::ratio<1>>;

}  // namespace breakout
