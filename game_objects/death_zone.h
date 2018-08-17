#pragma once
#include "box_collider.h"

namespace breakout {

class DeathZone : public StaticBoxCollider {
public:
  using StaticBoxCollider::StaticBoxCollider;

  void on_collision(GameObject* game_object) override {
    game_object->kill();
  }
};

}  // namespace breakout
