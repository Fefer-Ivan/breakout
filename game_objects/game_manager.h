#pragma once
#include "game_object.h"
#include <atomic>

namespace breakout {

class Player;

class GameManager : public GameObject {
public:
  GameManager(GameEngine* game_engine, size_t live_count, size_t score, size_t highscore) :
      GameObject(game_engine),
      live_count_(live_count),
      score_(score),
      highscore_(highscore),
      brick_count_(0),
      ball_count_(0),
      player_(nullptr) {}

  size_t live_count() const {
    return live_count_.load();
  }

  size_t score() const {
    return score_.load();
  }

  size_t highscore() const {
    return highscore_.load();
  }

  void set_player(Player* player) {
    player_ = player;
  }

  void add_score(size_t score);
  void add_lives(size_t lives);

  void on_brick_added();
  void on_brick_killed(size_t brick_score);

  void on_ball_added();
  void on_ball_killed();

private:
  std::atomic_size_t live_count_;
  std::atomic_size_t score_;
  std::atomic_size_t highscore_;
  size_t brick_count_;
  size_t ball_count_;

  Player* player_;
};

}  // namespace breakout
