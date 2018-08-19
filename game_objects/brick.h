#pragma once
#include "game_objects/game_manager.h"
#include "box_collider.h"

namespace breakout {

class Brick : public StaticBoxCollider {
public:
  void on_death() override {
    game_manager_->on_brick_killed(score_);
  }

  static constexpr double kBrickWidth = 5;
  static constexpr double kBrickHeight = 5;

protected:
  Brick(GameEngine* engine, const Vector2& center, GameManager* manager, size_t score) :
      StaticBoxCollider(engine, center, kBrickWidth, kBrickHeight),
      game_manager_(manager),
      score_(score) {
    game_manager_->on_brick_added();
  }

  GameManager* game_manager() const {
    return game_manager_;
  }

private:
  GameManager* game_manager_;
  size_t score_;
};

class CheapBrick : public Brick {
public:
  CheapBrick(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Brick(engine, center, manager, kCheapBrickScore) {}

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::Green);
  };

private:
  static constexpr size_t kCheapBrickScore = 10;
};

class MiddleBrick : public Brick {
public:
  MiddleBrick(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Brick(engine, center, manager, kMiddleBrickScore) {}

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::Yellow);
  };


private:
  static constexpr size_t kMiddleBrickScore = 20;
};

class ExpensiveBrick : public Brick {
public:
  ExpensiveBrick(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Brick(engine, center, manager, kExpensiveBrickScore) {}

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::Red);
  };

private:
  static constexpr size_t kExpensiveBrickScore = 50;
};

}  // namespace breakout

