#pragma once
#include "game_object.h"

namespace breakout {

class GameManager : public GameObject {
public:
  GameManager(GameEngine* game_engine, size_t live_count, size_t score) :
      GameObject(game_engine),
      live_count_(live_count),
      score_(score),
      brick_count_(0),
      ball_count_(0) {}

  size_t live_count() const {
    return live_count_;
  }

  size_t score() const {
    return score_;
  }

  void add_score(size_t score);
  void add_lives(size_t lives);

  void on_brick_added();
  void on_brick_killed(size_t brick_score);

  void on_ball_added();
  void on_ball_killed();

private:
  size_t live_count_;
  size_t score_;
  size_t brick_count_;
  size_t ball_count_;
};

}  // namespace breakout
