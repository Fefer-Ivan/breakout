#pragma once
#include "game_objects/game_manager.h"
#include "game_objects/text.h"

namespace breakout {

class ScoreText : public Text {
public:
  ScoreText(GameEngine* game_engine, Vector2 position, GameManager* game_manager) :
      Text(game_engine, position),
      game_manager_(game_manager) {}

private:
  std::string get_text() const override {
    return "score: " + std::to_string(game_manager_->score());
  }

  GameManager* game_manager_;
};

class HighscoreText : public Text {
public:
  HighscoreText(GameEngine* game_engine, Vector2 position, GameManager* game_manager) :
      Text(game_engine, position),
      game_manager_(game_manager) {}

private:
  std::string get_text() const override {
    return "highscore: " + std::to_string(game_manager_->highscore());
  }

  GameManager* game_manager_;
};

}  // namespace breakout
