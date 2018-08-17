#pragma once
#include "seconds.h"

namespace breakout {

class Timer {
public:
  Timer() : start_time_(std::chrono::high_resolution_clock::now()) {}

  Seconds get_duration_and_restart() {
    auto current_time = std::chrono::high_resolution_clock::now();
    auto duration = current_time - start_time_;
    start_time_ = std::chrono::high_resolution_clock::now();
    return duration;
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
};

}  // namespace breakout
