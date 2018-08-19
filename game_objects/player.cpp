#include "game_objects/player.h"
#include "game_objects/ball.h"
#include "game_engine.h"

namespace breakout {

void Player::update(Seconds time_delta) {
  set_velocity(Vector2(
      kPlayerSpeed * game_engine()->input_manager()->horizontal_axis(),
      0));
  DynamicBoxCollider::update(time_delta);
}

void Player::on_collision(GameObject* game_object) {
  auto box = dynamic_cast<const StaticBoxCollider*>(game_object);
  if (box == nullptr) {
    return;
  }

  if (box->center().x() < center().x()) {
    set_center(Vector2(box->center().x() + box->width() / 2 + width() / 2, center().y()));
  } else {
    set_center(Vector2(box->center().x() - box->width() / 2 - width() / 2, center().y()));
  }
}

void Player::draw(Canvas* canvas) const {
  canvas->draw_box(center(), width(), height(), Color::White);
};

void Player::create_ball() {
  game_engine()->create_game_object<Ball>(
      Vector2(
          center().x(),
          center().y() + height() / 2 + Ball::kBallHeight),
      game_manager_);
}

}  // namespace breakout

