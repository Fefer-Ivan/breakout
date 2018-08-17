#pragma once
#include "game_objects/game_manager.h"
#include "box_collider.h"

namespace breakout {

class Player : public DynamicBoxCollider {
public:
  Player(GameEngine* engine, const Vector2& center) :
      DynamicBoxCollider(engine, center, kPlayerWidth, kPlayerHeight, Vector2(0, 0)) {}

  void update(Seconds /*time_delta*/) {
    // TODO(ivanfefer): implement controls
  }

private:
  static constexpr double kPlayerWidth = 30;
  static constexpr double kPlayerHeight = 3;
};

}  // namespace breakout

