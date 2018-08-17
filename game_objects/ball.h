#pragma once
#include "game_objects/brick.h"
#include "game_objects/game_manager.h"
#include "game_objects/projectile.h"

namespace breakout {

class Ball : public Projectile<Brick> {
public:
  Ball(GameEngine* engine, const Vector2& center, GameManager* manager) :
      DynamicBoxCollider(engine, center, kBallWidth, kBallHeight, Vector2(kBallSpeed, kBallSpeed)),
      game_manager_(manager) {
    game_manager_->on_ball_added();
  }

  void on_death() override {
    game_manager_->on_ball_killed();
  }

  static constexpr double kBallWidth = 1;
  static constexpr double kBallHeight = 1;

private:
  static constexpr double kBallSpeed = 5;

  GameManager* game_manager_;
}

}  // namespace breakout
