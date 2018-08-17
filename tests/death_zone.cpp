#include "game_objects/death_zone.h"
#include <gtest/gtest.h>

using namespace breakout;

TEST(DeathZone, DeathZone) {
  DeathZone death_zone(nullptr, Vector2(0, 0), 0, 0);
  GameObject dead_object(nullptr);
  death_zone.on_collision(&dead_object);
  EXPECT_TRUE(dead_object.is_dead());
}
