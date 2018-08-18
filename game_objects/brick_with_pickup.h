#pragma once
#include "game_objects/brick.h"
#include "game_objects/pickup.h"
#include "game_objects/ball.h"

namespace breakout {

template<typename Pickup>
class BrickWithPickup : public Brick {
public:
  void on_death() override {
    Brick::on_death();
    game_engine()->template create_game_object<Pickup>(center(), game_manager());
  }

protected:
  using Brick::Brick;
};

class BrickWithExtraScore : public BrickWithPickup<ExtraScorePickup> {
public:
  BrickWithExtraScore(GameEngine* engine, const Vector2& center, GameManager* manager) :
      BrickWithPickup(engine, center, manager, kBrickWithExtraScoreScore) {}

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::DarkGreen);
  };

private:
  static constexpr size_t kBrickWithExtraScoreScore = 10;
};

class BrickWithExtraLife : public BrickWithPickup<ExtraLifePickup> {
public:
  BrickWithExtraLife(GameEngine* engine, const Vector2& center, GameManager* manager) :
      BrickWithPickup(engine, center, manager, kBrickWithExtraLifeScore) {}

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::DarkYellow);
  };

private:
  static constexpr size_t kBrickWithExtraLifeScore = 10;
};

class BrickWithExtraBall : public BrickWithPickup<ExtraBallPickup> {
public:
  BrickWithExtraBall(GameEngine* engine, const Vector2& center, GameManager* manager) :
      BrickWithPickup(engine, center, manager, kBrickWithExtraBallScore) {}

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::DarkRed);
  };

private:
  static constexpr size_t kBrickWithExtraBallScore = 10;
};

}  // namespace breakout


