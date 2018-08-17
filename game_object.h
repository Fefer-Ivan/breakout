#pragma once
#include "seconds.h"

namespace breakout {

class GameEngine;

class GameObject {
public:
  virtual void update(Seconds /*time_delta*/) {};
  virtual void on_death() {};
  virtual void draw() const {};

  void kill() {
    dead_ = true;
    on_death();
  }

  bool is_dead() const {
    return dead_;
  }

protected:
  GameEngine* game_engine() {
    return game_engine_;
  }

private:
  bool dead_;
  GameEngine* game_engine_;
};

}  // namespace breakout
