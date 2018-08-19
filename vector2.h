#pragma once

namespace breakout {

class Vector2 {
public:
  Vector2() : x_(0), y_(0) {}
  Vector2(double x, double y) : x_(x), y_(y) {}

  double x() const {
    return x_;
  }

  double y() const {
    return y_;
  }

  Vector2& operator += (const Vector2& rhs);
  Vector2& operator -= (const Vector2& rhs);
  Vector2& operator *= (double rhs);

private:
  double x_;
  double y_;
};

Vector2 operator + (const Vector2& lhs, const Vector2& rhs);
Vector2 operator - (const Vector2& lhs, const Vector2& rhs);
Vector2 operator * (const Vector2& lhs, double rhs);
Vector2 operator * (double lhs, const Vector2& rhs);
bool operator == (const Vector2& lhs, const Vector2& rhs);

}  // namespace breakout
