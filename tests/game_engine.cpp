#include "game_engine.h"
#include "box_collider.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace breakout;

namespace {

const double kExpectedError = 1e-5;

void expect_equal_seconds(Seconds actual, Seconds expected) {
  EXPECT_LT(std::abs(actual.count() - expected.count()), kExpectedError);
}

class DynamicSelfdestructOnCollision : public DynamicBoxCollider {
public:
  DynamicSelfdestructOnCollision(
      GameEngine* game_engine,
      Vector2 center,
      double width,
      double height,
      Vector2 velocity,
      Seconds expected_life_time) :
          DynamicBoxCollider(game_engine, center, width, height, velocity),
          life_time_(0s),
          expected_life_time_(expected_life_time) {}

  void update(Seconds time_delta) override {
    DynamicBoxCollider::update(time_delta);
    life_time_ += time_delta;
  }

  void on_collision(GameObject* /*game_object*/) override {
    kill();
  }

  void on_death() override {
    expect_equal_seconds(life_time_, expected_life_time_);
  }

private:
  Seconds life_time_;
  Seconds expected_life_time_;
};

class StaticSelfdestructOnCollision : public StaticBoxCollider {
public:
  StaticSelfdestructOnCollision(
      GameEngine* game_engine,
      Vector2 center,
      double width,
      double height,
      Seconds expected_life_time) :
          StaticBoxCollider(game_engine, center, width, height),
          life_time_(0s),
          expected_life_time_(expected_life_time) {}

  void update(Seconds time_delta) override {
    StaticBoxCollider::update(time_delta);
    life_time_ += time_delta;
  }

  void on_collision(GameObject* /*game_object*/) override {
    kill();
  }

  void on_death() override {
    expect_equal_seconds(life_time_, expected_life_time_);
  }

private:
  Seconds life_time_;
  Seconds expected_life_time_;
};

class TwoDynamicBoxesInstantTestLevel : public GameEngineRunner {
  void create_initial_game_objects() override {
    create_game_object<DynamicSelfdestructOnCollision>(
        Vector2(0, 0), 10, 10, Vector2(0, 0), 0s);
    create_game_object<DynamicSelfdestructOnCollision>(
        Vector2(5, 5), 10, 10, Vector2(0, 0), 0s);
  }
};

class TwoDynamicBoxesMoveTestLevel : public GameEngineRunner {
  void create_initial_game_objects() override {
    create_game_object<DynamicSelfdestructOnCollision>(
        Vector2(0, 0), 10, 10, Vector2(50, 50), 50ms);
    create_game_object<DynamicSelfdestructOnCollision>(
        Vector2(15, 15), 10, 10, Vector2(-50, -50), 50ms);
  }
};

class DynamicAndStaticBoxesMoveTestLevel : public GameEngineRunner {
  void create_initial_game_objects() override {
    create_game_object<DynamicSelfdestructOnCollision>(
        Vector2(0, 0), 10, 10, Vector2(50, 50), 100ms);
    create_game_object<StaticSelfdestructOnCollision>(
        Vector2(15, 15), 10, 10, 100ms);
  }
};

class SeveralBoxesMoveTestLevel : public GameEngineRunner {
  void create_initial_game_objects() override {
    create_game_object<DynamicSelfdestructOnCollision>(
        Vector2(0, 0), 10, 10, Vector2(50, 0), 100ms);
    create_game_object<StaticSelfdestructOnCollision>(
        Vector2(15, 0), 10, 10, 100ms);
    create_game_object<DynamicSelfdestructOnCollision>(
        Vector2(8, -2), 2, 2, Vector2(0, 50), 20ms);
    create_game_object<DynamicSelfdestructOnCollision>(
        Vector2(8, 2), 2, 2, Vector2(0, -50), 20ms);
  }
};

}  // namespace

TEST(GameEngine, TwoDynamicBoxesInstant) {
  TwoDynamicBoxesInstantTestLevel().run_main_loop();
}

TEST(GameEngine, TwoDynamicBoxesMove) {
  TwoDynamicBoxesMoveTestLevel().run_main_loop();
}

TEST(GameEngine, DynamicAndStaticBoxes) {
  DynamicAndStaticBoxesMoveTestLevel().run_main_loop();
}

TEST(GameEngine, SeveralBoxes) {
   SeveralBoxesMoveTestLevel().run_main_loop();
}
