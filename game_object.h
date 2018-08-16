#pragma once
#include "time.h"

namespace breakout {

class GameObject {
  virtual void start() {};
  virtual void update(Seconds /*time_delta*/) {};
  virtual void draw() {};
};

}  // namespace breakout