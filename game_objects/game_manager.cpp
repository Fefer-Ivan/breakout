#include "game_objects/game_manager.h"
#include "game_objects/player.h"
#include "game_engine.h"

namespace breakout {

void GameManager::add_score(size_t score) {
  score_ += score;
  if (highscore_ < score_) {
    highscore_ = score_;
  }
}

void GameManager::add_lives(size_t lives) {
  live_count_ += lives;
}

void GameManager::on_brick_added() {
  brick_count_++;
}

void GameManager::on_brick_killed(size_t brick_score) {
  brick_count_--;
  add_score(brick_score);
  if (brick_count_ == 0) {
    game_engine()->stop();
  }
}

void GameManager::on_ball_added() {
  ball_count_++;
}

void GameManager::on_ball_killed() {
  ball_count_--;
  if (ball_count_ == 0) {
    live_count_--;
    if (live_count_ == 0) {
      game_engine()->stop();
    } else {
      player_->create_ball();
    }
  }
}

}  // namespace breakout
