#include "timer.h"
#include <gtest/gtest.h>
#include <thread>

using namespace breakout;

const double kExpectedError = 0.001;

TEST(Timer, Timer) {
  auto sleep_duration = std::chrono::duration_cast<Seconds>(200ms);
  Timer timer;
  for (size_t i = 0; i < 3; ++i) {
    std::this_thread::sleep_for(sleep_duration);
    Seconds timer_duration = timer.get_duration_and_restart();
    EXPECT_LT((timer_duration - sleep_duration).count(), kExpectedError);
  }
}

