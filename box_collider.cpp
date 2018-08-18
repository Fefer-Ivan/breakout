#include "box_collider.h"
#include <cmath>

namespace breakout {

namespace {

bool has_collision_in_one_dimension(
    double lhs_center,
    double lhs_length,
    double rhs_center,
    double rhs_length) {
  return std::abs(lhs_center - rhs_center) <= (lhs_length + rhs_length) / 2;
}

}  // namespace

bool BoxCollider::has_collision(const BoxCollider& rhs) const {
  return
      has_collision_in_one_dimension(center().x(), width(), rhs.center().x(), rhs.width()) &&
      has_collision_in_one_dimension(center().y(), height(), rhs.center().y(), rhs.height());
}

void DynamicBoxCollider::update(Seconds time_delta) {
  set_center(center() + velocity() * time_delta.count());
}

}  // namespace breakout
