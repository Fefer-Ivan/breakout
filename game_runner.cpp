#include "game_runner.h"
#include "canvas.h"
#include "game_objects/game_manager.h"
#include "game_objects/ball.h"
#include "game_objects/brick.h"
#include <iostream>

namespace breakout {

GameRunner::GameRunner() : game_running_(false), lifes_(kStartLifes), score_(0) {
}

GameRunner::~GameRunner() {
  stop();
}

void GameRunner::start() {
  game_running_.store(true);
  game_thread_ = std::make_unique<std::thread>([this] () {
    while (game_running_.load()) {
      run_main_loop();
      reset();
      lifes_ = game_manager_->live_count();
      score_ = game_manager_->score();
      std::clog << "level finished with lifes " << lifes_ << " score " << score_ << std::endl;
      if (lifes_ == 0) {
        lifes_ = kStartLifes;
        score_ = 0;
      }
    }
  });
}

void GameRunner::stop() {
  game_running_.store(false);
  GameEngine::stop();
  if (game_thread_ != nullptr) {
    game_thread_->join();
  }
}

void GameRunner::create_initial_game_objects() {
  game_manager_ = create_game_object<GameManager>(lifes_, score_);
  create_game_object<CheapBrick>(Vector2(50, 50), game_manager_.get());
  create_game_object<Ball>(Vector2(40, 40), game_manager_.get());
}

}  // namespace breakout

