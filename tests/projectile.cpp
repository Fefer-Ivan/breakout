#include "game_objects/projectile.h"
#include <gtest/gtest.h>

using namespace breakout;

TEST(Projectile, HitTarget) {
  Projectile<StaticBoxCollider> p(nullptr, Vector2(0, 0), 2, 2, Vector2(0, 0));
  StaticBoxCollider t(nullptr, Vector2(2, 0), 2, 2);
  p.on_collision(&t);
  EXPECT_TRUE(t.is_dead());
}

TEST(Projectile, HitNotTarget) {
  Projectile<DynamicBoxCollider> p(nullptr, Vector2(0, 0), 2, 2, Vector2(0, 0));
  StaticBoxCollider t(nullptr, Vector2(2, 0), 2, 2);
  p.on_collision(&t);
  EXPECT_FALSE(t.is_dead());
}

TEST(Projectile, HitRightSide) {
  Projectile<DynamicBoxCollider> p(nullptr, Vector2(0, 0), 2, 2, Vector2(1, 1));
  StaticBoxCollider t(nullptr, Vector2(2, 0), 2, 2);
  p.on_collision(&t);
  EXPECT_EQ(p.velocity().x(), -1);
  EXPECT_EQ(p.velocity().y(), 1);
}

TEST(Projectile, HitLeftSide) {
  Projectile<DynamicBoxCollider> p(nullptr, Vector2(0, 0), 2, 2, Vector2(-1, 1));
  StaticBoxCollider t(nullptr, Vector2(-2, 0), 2, 2);
  p.on_collision(&t);
  EXPECT_EQ(p.velocity().x(), 1);
  EXPECT_EQ(p.velocity().y(), 1);
}

TEST(Projectile, HitTopSide) {
  Projectile<DynamicBoxCollider> p(nullptr, Vector2(0, 0), 2, 2, Vector2(1, 1));
  StaticBoxCollider t(nullptr, Vector2(0, 2), 2, 2);
  p.on_collision(&t);
  EXPECT_EQ(p.velocity().x(), 1);
  EXPECT_EQ(p.velocity().y(), -1);
}

TEST(Projectile, HitBottomSide) {
  Projectile<DynamicBoxCollider> p(nullptr, Vector2(0, 0), 2, 2, Vector2(1, -1));
  StaticBoxCollider t(nullptr, Vector2(0, -2), 2, 2);
  p.on_collision(&t);
  EXPECT_EQ(p.velocity().x(), 1);
  EXPECT_EQ(p.velocity().y(), 1);
}

TEST(Projectile, HitCorner) {
  Projectile<DynamicBoxCollider> p(nullptr, Vector2(0, 0), 2, 2, Vector2(1, 1));
  StaticBoxCollider t(nullptr, Vector2(2, 2), 2, 2);
  p.on_collision(&t);
  EXPECT_EQ(p.velocity().x(), -1);
  EXPECT_EQ(p.velocity().y(), -1);
}
