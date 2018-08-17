#include "game_objects/collectable.h"
#include <gtest/gtest.h>

using namespace breakout;

namespace {

class CollectableByStaticBoxCollider : public Collectable<StaticBoxCollider> {
public:
  using Collectable::Collectable;

  void on_collection(StaticBoxCollider* /*collector*/) override {
    collected_ = true;
  }

  bool is_collected() const {
    return collected_;
  }

private:
  bool collected_ = false;
};

}  // namespace

TEST(Collectable, CollisionWithCollector) {
  CollectableByStaticBoxCollider c(nullptr, Vector2(0, 0), 2, 2, Vector2(0, 0));
  StaticBoxCollider b(nullptr, Vector2(2, 0), 2, 2);
  c.on_collision(&b);
  EXPECT_TRUE(c.is_dead());
  EXPECT_TRUE(c.is_collected());
}

TEST(Collectable, CollisionNotWithCollector) {
  CollectableByStaticBoxCollider c(nullptr, Vector2(0, 0), 2, 2, Vector2(0, 0));
  DynamicBoxCollider b(nullptr, Vector2(2, 0), 2, 2, Vector2(0, 0));
  c.on_collision(&b);
  EXPECT_FALSE(c.is_dead());
  EXPECT_FALSE(c.is_collected());
}
