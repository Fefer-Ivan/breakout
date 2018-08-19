#pragma once
#include "game_objects/game_manager.h"
#include "game_objects/text.h"
#include <string>

namespace breakout {

class LivesText : public Text {
public:
  LivesText(GameEngine* game_engine, Vector2 position, GameManager* game_manager) :
      Text(game_engine, position),
      game_manager_(game_manager) {}

private:
  std::string get_text() const override {
    return "lives: " + std::to_string(game_manager_->live_count());
  }

  GameManager* game_manager_;
};

}  // namespace breakout
