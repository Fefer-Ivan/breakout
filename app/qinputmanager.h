#pragma once
#include "input_manager.h"

namespace breakout {

class QInputManager : public InputManager {
public:
  void press_key(int key);

  void release_key(int key);

private:
  bool update_counters(int key, int modificator);
  void update_horizontal_axis();

  int negative_horizontal_keys_count_;
  int positive_horizontal_keys_count_;
};

}  // namespace breakout
