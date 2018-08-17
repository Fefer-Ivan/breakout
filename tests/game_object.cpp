#include "game_object.h"
#include <gtest/gtest.h>
#include <memory>

using namespace breakout;

namespace {

class OnDeathCallCounter : public GameObject {
public:
  OnDeathCallCounter(GameEngine* game_engine) : GameObject(game_engine), on_death_call_count_(0) {}

  void on_death() override {
    on_death_call_count_++;
  }

  size_t on_death_call_count() const {
    return on_death_call_count_;
  }

private:
  size_t on_death_call_count_;
};

}  // namespace

TEST(GameObject, KilledTwice) {
  auto game_object = std::make_unique<OnDeathCallCounter>(nullptr);
  for (size_t i = 0; i < 2; ++i) {
    game_object->kill();
    EXPECT_TRUE(game_object->is_dead());
    EXPECT_EQ(game_object->on_death_call_count(), 1);
  }
}
