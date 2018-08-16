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

  Vector2& operator += (const Vector2& rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
  }

  Vector2& operator -= (const Vector2& rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
  }

  Vector2& operator *= (double rhs) {
    x_ *= rhs;
    y_ *= rhs;
    return *this;
  }

private:
  double x_;
  double y_;
};

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
