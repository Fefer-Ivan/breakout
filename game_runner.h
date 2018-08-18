#pragma once
#include "game_engine.h"
#include <atomic>
#include <memory>
#include <thread>

namespace breakout {

class Canvas;
class GameManager;

class GameRunner : public GameEngineRunner {
public:
  GameRunner();
  ~GameRunner();

  void start();
  void stop();

  void create_initial_game_objects() override;

private:
  static constexpr size_t kStartLifes = 3;

  std::atomic_bool game_running_;
  std::shared_ptr<GameManager> game_manager_;
  size_t lifes_;
  size_t score_;
  std::unique_ptr<std::thread> game_thread_;
};

}  // namespace breakout
