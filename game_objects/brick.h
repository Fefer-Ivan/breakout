#pragma once
#include "game_objects/game_manager.h"
#include "game_objects/pickup.h"
#include "box_collider.h"

namespace breakout {

class Brick : public StaticBoxCollider {
public:
  void on_death() override {
    game_manager_->on_brick_killed(score_);
  }

protected:
  Brick(GameEngine* engine, const Vector2& center, GameManager* manager, size_t score) :
      StaticBoxCollider(engine, center, kBrickWidth, kBrickHeight),
      game_manager_(manager),
      score_(score) {
    game_manager_->on_brick_added();
  }

  GameManager() game_manager() const {
    return game_manager_;
  }

private:
  static constexpr double kBrickWidth = 10;
  static constexpr double kBrickHeight = 10;

  GameManager* game_manager_;
  size_t score_;
};

class CheapBrick : public Brick {
public:
  CheapBrick(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Brick(engine, center, manager, kCheapBrickScore) {}

private:
  static constexpr kCheapBrickScore = 10;
}

class MiddleBrick : public Brick {
public:
  MiddleBrick(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Brick(engine, center, manager, kMiddleBrickScore) {}

private:
  static constexpr kMiddleBrickScore = 20;
}

class ExpensiveBrick : public Brick {
public:
  ExpensiveBrick(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Brick(engine, center, manager, kExpensiveBrickScore) {}

private:
  static constexpr kExpensiveBrickScore = 50;
}

template<typename Pickup>
class BrickWithPickup : public Brick {
public:
  void on_death() override {
    Brick::on_death();
    game_engine()->create_game_object<Pickup>(center(), game_manager());
  }

protected:
  using Brick::Brick;
};

class BrickWithExtraScore : public BrickWithPickup<ExtraScorePickup> {
public:
  BrickWithExtraScore(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Brick(engine, center, manager, kBrickWithExtraScoreScore) {}

private:
  static constexpr kBrickWithExtraScoreScore = 10;
}

class BrickWithExtraLife : public BrickWithPickup<ExtraLifePickup> {
public:
  BrickWithExtraLife(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Brick(engine, center, manager, kBrickWithExtraLifeScore) {}

private:
  static constexpr kBrickWithExtraLifeScore = 10;
}

class BrickWithExtraBall : public BrickWithPickup<ExtraBallPickup> {
public:
  BrickWithExtraBall(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Brick(engine, center, manager, kBrickWithExtraBallScore) {}

private:
  static constexpr kBrickWithExtraBallScore = 10;
}

}  // namespace breakout

