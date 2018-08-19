#pragma once
#include <array>
#include <atomic>

namespace breakout {

class InputManager {
public:
  virtual ~InputManager() = default;

  double horizontal_axis() const {
    return horizontal_axis_.load();
  }

protected:
  void set_horizontal_axis(double horizontal_axis) {
    horizontal_axis_.store(horizontal_axis);
  }

private:
  std::atomic<double> horizontal_axis_;
};

}  // namespace breakout
