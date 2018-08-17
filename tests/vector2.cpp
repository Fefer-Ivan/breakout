#include "vector2.h"
#include <gtest/gtest.h>

using namespace breakout;

TEST(Vector2, DefaultConstructor) {
  Vector2 v;
  EXPECT_EQ(v.x(), 0);
  EXPECT_EQ(v.y(), 0);
}

TEST(Vector2, Constructor) {
  Vector2 v(1, 2);
  EXPECT_EQ(v.x(), 1);
  EXPECT_EQ(v.y(), 2);
}

TEST(Vector2, AddAssign) {
  Vector2 v(1, 2);
  v += Vector2(3, 4);
  EXPECT_EQ(v.x(), 4);
  EXPECT_EQ(v.y(), 6);
}

TEST(Vector2, Add) {
  Vector2 v = Vector2(1, 2) + Vector2(3, 4);
  EXPECT_EQ(v.x(), 4);
  EXPECT_EQ(v.y(), 6);
}

TEST(Vector2, SubAssign) {
  Vector2 v(1, 2);
  v -= Vector2(4, 3);
  EXPECT_EQ(v.x(), -3);
  EXPECT_EQ(v.y(), -1);
}

TEST(Vector2, Sub) {
  Vector2 v = Vector2(1, 2) - Vector2(4, 3);
  EXPECT_EQ(v.x(), -3);
  EXPECT_EQ(v.y(), -1);
}

TEST(Vector2, MulAssign) {
  Vector2 v(1, 2);
  v *= -3;
  EXPECT_EQ(v.x(), -3);
  EXPECT_EQ(v.y(), -6);
}

TEST(Vector2, Mul) {
  Vector2 v = Vector2(1, 2) * 3;
  EXPECT_EQ(v.x(), 3);
  EXPECT_EQ(v.y(), 6);
}

TEST(Vector2, Mul2) {
  Vector2 v = -3 * Vector2(-1, 2);
  EXPECT_EQ(v.x(), 3);
  EXPECT_EQ(v.y(), -6);
}

TEST(Vector2, Expression) {
  Vector2 v = 3 * (Vector2(0, 1) + Vector2(3, 0) * 2) - Vector2(-1, -3) * 3;
  EXPECT_EQ(v.x(), 21);
  EXPECT_EQ(v.y(), 12);
}
