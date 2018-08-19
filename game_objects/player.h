#pragma once
#include "game_objects/game_manager.h"
#include "box_collider.h"

namespace breakout {

class Player : public DynamicBoxCollider {
public:
  Player(GameEngine* engine, const Vector2& center, GameManager* game_manager) :
      DynamicBoxCollider(engine, center, kPlayerWidth, kPlayerHeight, Vector2(0, 0)),
      game_manager_(game_manager) {}

  void update(Seconds /*time_delta*/) override {
    // TODO(ivanfefer): implement controls
  }

  void on_collision(GameObject* /*game_object*/) override {
    // TODO(ivanfefer): prevent going out of bounds
  }

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::DarkGreen);
  };

  void create_ball() {
    game_engine()->create_game_object<Ball>(
        Vector2(
            center().x(),
            center().y() + height() / 2 + Ball::kBallHeight),
        game_manager_);
  }

private:
  static constexpr double kPlayerWidth = 20;
  static constexpr double kPlayerHeight = 3;

  GameManager* game_manager_;
};

}  // namespace breakout

