#pragma once
#include "game_object.h"
#include "vector2.h"

namespace breakout {

enum class MovementType {
  Static,
  Dynamic
};

class BoxCollider : public GameObject {
public:
  BoxCollider(MovementType movement_type, const Vector2& center, double width, double height) :
      movement_type_(movement_type), center_(center), width_(width), height_(height) {}

  bool has_collision(const BoxCollider& rhs) const;

  virtual void on_collision(GameObject* /*game_object*/) {};

  MovementType movement_type() const {
    return movement_type_;
  }

  const Vector2& center() const {
    return center_;
  }

  double width() const {
    return width_;
  }

  double height() const {
    return height_;
  }

protected:
  void set_center(const Vector2& center) {
    center_ = center;
  }

private:
  MovementType movement_type_;
  Vector2 center_;
  double width_;
  double height_;
};

class StaticBoxCollider : public BoxCollider {
public:
  StaticBoxCollider(const Vector2& center, double width, double height) :
      BoxCollider(MovementType::Static, center, width, height) {}
};

class DynamicBoxCollider : public BoxCollider {
public:
  DynamicBoxCollider(const Vector2& center, double width, double height) :
      BoxCollider(MovementType::Dynamic, center, width, height) {}

  void update(Seconds time_delta) override;

protected:
  const Vector2& velocity() const {
    return velocity_;
  }

  void set_velocity(const Vector2& velocity) {
    velocity_ = velocity;
  }

private:
  Vector2 velocity_;
};

}  // namespace breakout

