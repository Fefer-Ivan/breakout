#pragma once
#include "seconds.h"

namespace breakout {

class GameEngine;
class Canvas;

class GameObject {
public:
  GameObject(GameEngine* game_engine) : game_engine_(game_engine), dead_(false) {}
  virtual ~GameObject() = default;

  virtual void update(Seconds /*time_delta*/) {};
  virtual void on_death() {};
  virtual void draw(Canvas* /*canvas*/) const {};

  void kill() {
    if (!dead_) {
      dead_ = true;
      on_death();
    }
  }

  bool is_dead() const {
    return dead_;
  }

protected:
  GameEngine* game_engine() {
    return game_engine_;
  }

private:
  GameEngine* game_engine_;
  bool dead_;
};

}  // namespace breakout
