#include "game_runner.h"
#include "canvas.h"
#include "game_objects/ball.h"
#include "game_objects/brick.h"
#include "game_objects/brick_with_pickup.h"
#include "game_objects/death_zone.h"
#include "game_objects/game_manager.h"
#include "game_objects/lives_text.h"
#include "game_objects/player.h"
#include "game_objects/score_text.h"
#include <iostream>
#include <limits>

namespace breakout {

GameRunner::GameRunner(std::unique_ptr<InputManager> input_manager) :
    GameEngineRunner(std::move(input_manager)),
    game_running_(false),
    lifes_(kStartLifes),
    score_(0) {}

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
  create_bounding_box();
  create_texts(game_manager_.get());
  create_player_and_ball(game_manager_.get());
  create_bricks(game_manager_.get());
}

void GameRunner::create_bounding_box() {
  create_game_object<StaticBoxCollider>(Vector2(-0.5, kGameFieldHeight / 2), 1, kGameFieldHeight);
  create_game_object<StaticBoxCollider>(Vector2(kGameFieldWidth + 0.5, kGameFieldHeight / 2), 1, kGameFieldHeight);
  create_game_object<StaticBoxCollider>(Vector2(kGameFieldWidth / 2, kGameFieldHeight + 0.5), kGameFieldWidth, 1);
  create_game_object<DeathZone>(Vector2(kGameFieldWidth / 2, -0.5), kGameFieldWidth, 1);
}

void GameRunner::create_texts(GameManager* game_manager) {
  create_game_object<LivesText>(Vector2(1, 10), game_manager);
  create_game_object<ScoreText>(Vector2(1, 12), game_manager);
}

void GameRunner::create_player_and_ball(GameManager* game_manager) {
  auto player = create_game_object<Player>(Vector2(kGameFieldWidth / 2, 2), game_manager);
  player->create_ball();
}

void GameRunner::create_bricks(GameManager* game_manager) {
  create_brick_row<CheapBrick, BrickWithExtraScore>(80, game_manager);
  create_brick_row<MiddleBrick, BrickWithExtraLife>(85, game_manager);
  create_brick_row<ExpensiveBrick, BrickWithExtraBall>(90, game_manager);
}

template<typename StandardBrick, typename PickupBrick>
void GameRunner::create_brick_row(double y, GameManager* game_manager) {
  double brick_width = StandardBrick::kBrickWidth;
  size_t brick_count = static_cast<size_t>(kGameFieldWidth / brick_width +
      std::numeric_limits<double>::epsilon());
  for (size_t brick_index = 0; brick_index < brick_count; ++brick_index) {
    double x = brick_width / 2 + brick_index * brick_width;
    if (brick_index % 5 == 2) {
      create_game_object<PickupBrick>(Vector2(x, y), game_manager);
    } else {
      create_game_object<StandardBrick>(Vector2(x, y), game_manager);
    }
  }
}

}  // namespace breakout

