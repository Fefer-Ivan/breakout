#pragma once
#include "box_collider.h"
#include <utility>
#include <cmath>

namespace breakout {

template<typename Target>
class Projectile : public DynamicBoxCollider {
public:
  using DynamicBoxCollider::DynamicBoxCollider;

  void on_collision(GameObject* game_object) override {
    change_velocity(static_cast<BoxCollider*>(game_object));
    if (dynamic_cast<Target*>(game_object) != nullptr) {
      game_object->kill();
    }
  }

private:
  static constexpr double kExpectedError = 1e-5;

  void change_velocity(const BoxCollider* box_collider) {
    double x_intersection = get_intersection(get_x_segment(this), get_x_segment(box_collider));
    double y_intersection = get_intersection(get_y_segment(this), get_y_segment(box_collider));
    if (std::abs(x_intersection - y_intersection) < kExpectedError) {
      set_velocity(Vector2(-velocity().x(), -velocity().y()));
    } else if (x_intersection > y_intersection) {
      set_velocity(Vector2(velocity().x(), -velocity().y()));
    } else {
      set_velocity(Vector2(-velocity().x(), velocity().y()));
    }
  }

  static std::pair<double, double> get_x_segment(const BoxCollider* box) {
    return get_segment(box->center().x(), box->width());
  }

  static std::pair<double, double> get_y_segment(const BoxCollider* box) {
    return get_segment(box->center().y(), box->height());
  }

  static std::pair<double, double> get_segment(double center, double length) {
    return {center - length / 2, center + length / 2};
  }

  static double get_intersection(
      const std::pair<double, double>& lhs,
      const std::pair<double, double>& rhs) {
    return std::min(lhs.second, rhs.second) - std::max(lhs.first, rhs.first);
  }
};

}  // namespace breakout
