#include "game_objects/ball.h"
#include "game_objects/pickup.h"
#include "game_objects/player.h"

namespace breakout {

void Ball::on_collision(GameObject* game_object) {
  if (should_ignore_collision(game_object)) {
    return;
  }
  auto player = dynamic_cast<const Player*>(game_object);
  if (player != nullptr) {
    on_player_collision(player);
  }
  Projectile::on_collision(game_object);
}

bool Ball::should_ignore_collision(const GameObject* game_object) const {
  return dynamic_cast<const Pickup*>(game_object) != nullptr ||
      dynamic_cast<const Ball*>(game_object) != nullptr;
}

void Ball::on_player_collision(const Player* player) {
  set_velocity(Vector2(
    player->center().x() < center().x() ? kBallSpeed : -kBallSpeed,
    kBallSpeed));
}

}  // namespace breakout

