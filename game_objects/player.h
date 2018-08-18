#pragma once
#include "game_objects/game_manager.h"
#include "box_collider.h"

namespace breakout {

class Player : public DynamicBoxCollider {
public:
  Player(GameEngine* engine, const Vector2& center) :
      DynamicBoxCollider(engine, center, kPlayerWidth, kPlayerHeight, Vector2(0, 0)) {}

  void update(Seconds /*time_delta*/) override {
    // TODO(ivanfefer): implement controls
  }

  void on_collision(GameObject* /*game_object*/) override {
    // TODO(ivanfefer): prevent going out of bounds
  }

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::DarkGreen);
  };

private:
  static constexpr double kPlayerWidth = 30;
  static constexpr double kPlayerHeight = 3;
};

}  // namespace breakout

