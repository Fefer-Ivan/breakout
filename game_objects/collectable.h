#pragma once
#include "box_collider.h"
#include <utility>
#include <cmath>

namespace breakout {

template<typename Collector>
class Collectable : public DynamicBoxCollider {
public:
  using DynamicBoxCollider::DynamicBoxCollider;

  void on_collision(GameObject* game_object) override {
    auto* collector = dynamic_cast<Collector*>(game_object);
    if (collector != nullptr) {
      on_collection(collector);
      kill();
    }
  }

  virtual void on_collection(Collector* collector) = 0;
};

}  // namespace breakout

