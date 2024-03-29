#pragma once
#include "canvas.h"
#include "game_objects/brick.h"
#include "game_objects/game_manager.h"
#include "game_objects/projectile.h"

namespace breakout {

class Player;

class Ball : public Projectile<Brick> {
public:
  Ball(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Projectile(engine, center, kBallWidth, kBallHeight, Vector2(kBallSpeed, kBallSpeed)),
      game_manager_(manager) {
    game_manager_->on_ball_added();
  }

  void on_collision(GameObject* game_object) override;

  void on_death() override {
    game_manager_->on_ball_killed();
  }

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::White);
  };

  static constexpr double kBallWidth = 1;
  static constexpr double kBallHeight = 1;

private:
  static constexpr double kBallSpeed = 50;

  bool should_ignore_collision(const GameObject* game_object) const;
  void on_player_collision(const Player* player);

  GameManager* game_manager_;
};

}  // namespace breakout
