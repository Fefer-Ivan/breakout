#include "vector2.h"

namespace breakout {


Vector2& Vector2::operator += (const Vector2& rhs) {
  x_ += rhs.x_;
  y_ += rhs.y_;
  return *this;
}

Vector2& Vector2::operator -= (const Vector2& rhs) {
  x_ -= rhs.x_;
  y_ -= rhs.y_;
  return *this;
}

Vector2& Vector2::operator *= (double rhs) {
  x_ *= rhs;
  y_ *= rhs;
  return *this;
}

Vector2 operator + (const Vector2& lhs, const Vector2& rhs) {
  return Vector2(lhs) += rhs;
}

Vector2 operator - (const Vector2& lhs, const Vector2& rhs) {
  return Vector2(lhs) -= rhs;
}

Vector2 operator * (const Vector2& lhs, double rhs) {
  return Vector2(lhs) * rhs;
}

Vector2 operator * (double lhs, const Vector2& rhs) {
  return rhs * lhs;
}

}  // namespace breakout

