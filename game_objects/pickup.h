#pragma once
#include "game_objects/ball.h"
#include "game_objects/collectable.h"
#include "game_objects/game_manager.h"
#include "game_objects/player.h"
#include "box_collider.h"

namespace breakout {

class Pickup : public Collectable<Player> {
public:
  Pickup(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Collectable(engine, center, kPickupWidth, kPickupHeight, Vector2(0, -kPickupSpeed)),
      game_manager_(manager) {}

  GameManager* game_manager() const {
    return game_manager_;
  }

private:
  static constexpr double kPickupWidth = 2;
  static constexpr double kPickupHeight = 2;
  static constexpr double kPickupSpeed = 30;

  GameManager* game_manager_;
};

class ExtraScorePickup : public Pickup {
public:
  ExtraScorePickup(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Pickup(engine, center, manager) {}

  void on_collection(Player* /*player*/) override {
    game_manager()->add_score(kPickupExtraScore);
  }

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::DarkGreen);
  }

private:
  static constexpr size_t kPickupExtraScore = 100;
};

class ExtraLifePickup : public Pickup {
public:
  ExtraLifePickup(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Pickup(engine, center, manager) {}

  void on_collection(Player* /*player*/) override {
    game_manager()->add_lives(1);
  }

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::DarkYellow);
  }
};

class ExtraBallPickup : public Pickup {
public:
  ExtraBallPickup(GameEngine* engine, const Vector2& center, GameManager* manager) :
      Pickup(engine, center, manager) {}

  void on_collection(Player* player) override {
    player->create_ball();
  }

  void draw(Canvas* canvas) const override {
    canvas->draw_box(center(), width(), height(), Color::DarkRed);
  }
};

}  // namespace breakout

