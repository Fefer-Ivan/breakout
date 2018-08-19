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
  bool has_collision(const BoxCollider& rhs) const;

  virtual void on_collision(GameObject* /*game_object*/) {}

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
  BoxCollider(
      GameEngine* game_engine,
      MovementType movement_type,
      const Vector2& center,
      double width,
      double height) :
          GameObject(game_engine),
          movement_type_(movement_type), center_(center), width_(width), height_(height) {}

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
  StaticBoxCollider(GameEngine* game_engine, const Vector2& center, double width, double height) :
      BoxCollider(game_engine, MovementType::Static, center, width, height) {}
};

class DynamicBoxCollider : public BoxCollider {
public:
  DynamicBoxCollider(
      GameEngine* game_engine,
      const Vector2& center,
      double width,
      double height,
      const Vector2& velocity) :
          BoxCollider(game_engine, MovementType::Dynamic, center, width, height), velocity_(velocity) {}

  void update(Seconds time_delta) override;

  const Vector2& velocity() const {
    return velocity_;
  }

protected:
  void set_velocity(const Vector2& velocity) {
    velocity_ = velocity;
  }

private:
  Vector2 velocity_;
};

}  // namespace breakout

