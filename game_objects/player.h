#pragma once
#include "game_objects/game_manager.h"
#include "box_collider.h"

namespace breakout {

class Player : public DynamicBoxCollider {
public:
  Player(GameEngine* engine, const Vector2& center, GameManager* game_manager) :
      DynamicBoxCollider(engine, center, kPlayerWidth, kPlayerHeight, Vector2(0, 0)),
      game_manager_(game_manager) {}

  void update(Seconds time_delta) override;

  void on_collision(GameObject* game_object) override;

  void draw(Canvas* canvas) const override;

  void create_ball();

private:
  static constexpr double kPlayerWidth = 20;
  static constexpr double kPlayerHeight = 3;
  static constexpr double kPlayerSpeed = 40;

  GameManager* game_manager_;
};

}  // namespace breakout

