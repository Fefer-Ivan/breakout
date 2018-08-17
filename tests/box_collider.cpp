#include "box_collider.h"
#include <gtest/gtest.h>

using namespace breakout;

TEST(BoxCollider, CollisionFar) {
  StaticBoxCollider a(nullptr, Vector2(0, 0), 10, 10);
  StaticBoxCollider b(nullptr, Vector2(100, 100), 10, 10);
  EXPECT_FALSE(a.has_collision(b));
  EXPECT_FALSE(b.has_collision(a));
}

TEST(BoxCollider, CollisionNear) {
  StaticBoxCollider a(nullptr, Vector2(0, 0), 10, 10);
  StaticBoxCollider b(nullptr, Vector2(11, 11), 10, 10);
  EXPECT_FALSE(a.has_collision(b));
  EXPECT_FALSE(b.has_collision(a));
}

TEST(BoxCollider, CollisionOnY) {
  StaticBoxCollider a(nullptr, Vector2(0, 0), 10, 10);
  StaticBoxCollider b(nullptr, Vector2(11, 4), 10, 10);
  EXPECT_FALSE(a.has_collision(b));
  EXPECT_FALSE(b.has_collision(a));
}

TEST(BoxCollider, CollisionOnX) {
  StaticBoxCollider a(nullptr, Vector2(0, 0), 10, 10);
  StaticBoxCollider b(nullptr, Vector2(-4, 11), 10, 10);
  EXPECT_FALSE(a.has_collision(b));
  EXPECT_FALSE(b.has_collision(a));
}

TEST(BoxCollider, CollisionTouchY) {
  StaticBoxCollider a(nullptr, Vector2(0, 0), 10, 10);
  StaticBoxCollider b(nullptr, Vector2(0, 7), 4, 4);
  EXPECT_TRUE(a.has_collision(b));
  EXPECT_TRUE(b.has_collision(a));
}

TEST(BoxCollider, CollisionTouchX) {
  StaticBoxCollider a(nullptr, Vector2(0, 0), 10, 10);
  StaticBoxCollider b(nullptr, Vector2(7, 0), 4, 4);
  EXPECT_TRUE(a.has_collision(b));
  EXPECT_TRUE(b.has_collision(a));
}

TEST(BoxCollider, CollisionTouchCorner) {
  StaticBoxCollider a(nullptr, Vector2(0, 0), 10, 10);
  StaticBoxCollider b(nullptr, Vector2(-7, -7), 4, 4);
  EXPECT_TRUE(a.has_collision(b));
  EXPECT_TRUE(b.has_collision(a));
}

TEST(BoxCollider, CollisionInside) {
  StaticBoxCollider a(nullptr, Vector2(0, 0), 10, 10);
  StaticBoxCollider b(nullptr, Vector2(2, 2), 4, 4);
  EXPECT_TRUE(a.has_collision(b));
  EXPECT_TRUE(b.has_collision(a));
}

TEST(BoxCollider, CollisionIntersect) {
  StaticBoxCollider a(nullptr, Vector2(0, 0), 10, 10);
  StaticBoxCollider b(nullptr, Vector2(-4, -4), 4, 4);
  EXPECT_TRUE(a.has_collision(b));
  EXPECT_TRUE(b.has_collision(a));
}

TEST(BoxCollider, DynamicUpdate) {
  Vector2 v(10, 10);
  DynamicBoxCollider d(nullptr, Vector2(0, 0), 1, 1, v);
  d.update(0.5s);
  EXPECT_EQ(d.center().x(), 5);
  EXPECT_EQ(d.center().y(), 5);
  d.update(1s);
  EXPECT_EQ(d.center().x(), 15);
  EXPECT_EQ(d.center().y(), 15);
}

TEST(BoxCollider, DynamicUpdateZeroVelocity) {
  Vector2 v(0, 0);
  DynamicBoxCollider d(nullptr, Vector2(0, 0), 1, 1, v);
  d.update(100s);
  EXPECT_EQ(d.center().x(), 0);
  EXPECT_EQ(d.center().y(), 0);
}
