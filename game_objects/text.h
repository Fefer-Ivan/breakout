#pragma once
#include "game_object.h"
#include "vector2.h"
#include <string>

namespace breakout {

class Text : public GameObject {
public:
  Text(GameEngine* game_engine, Vector2 position) : GameObject(game_engine), position_(position) {}

  void draw(Canvas* canvas) const override {
    canvas->draw_text(position_, get_text(), Color::White);
  }

private:
  virtual std::string get_text() const = 0;

  Vector2 position_;
};

}  // namespace breakout
