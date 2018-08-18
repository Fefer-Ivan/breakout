#include "game_engine.h"
#include "box_collider.h"
#include "game_object.h"
#include "timer.h"
#include <algorithm>
#include <iterator>
#include <iostream>

namespace breakout {

namespace {

constexpr Seconds kMaxTimeDelta = 0.06s;

template<typename Container, typename Predicate>
void remove_if(Container& container, const Predicate& predicate) {
  auto new_end = std::remove_if(std::begin(container), std::end(container), predicate);
  container.erase(new_end, container.end());
}

template<typename LhsColliderPtr, typename RhsColliderIt>
void handle_collisions_range(
    LhsColliderPtr& lhs_collider,
    RhsColliderIt rhs_collider_first,
    RhsColliderIt rhs_collider_last) {
  while (rhs_collider_first != rhs_collider_last) {
    auto& rhs_collider = *rhs_collider_first++;
    if (lhs_collider->has_collision(*rhs_collider)) {
      lhs_collider->on_collision(rhs_collider.get());
      rhs_collider->on_collision(lhs_collider.get());
    }
  }
}

}  // namespace

GameEngine::~GameEngine() = default;

void GameEngine::run_main_loop() {
  Timer timer;
  while (!stopped_ && !game_objects_.empty()) {
    auto time_delta = std::min(kMaxTimeDelta, timer.get_duration_and_restart());
    update(time_delta);
    handle_collisions();
    remove_dead_objects();
    draw();
  }
}

void GameEngine::update(const Seconds& time_delta) {
  for (auto& game_object : game_objects_) {
    game_object->update(time_delta);
  }
}

void GameEngine::handle_collisions() {
  for (size_t lhs_collider_index = 0; lhs_collider_index < dynamic_colliders_.size(); ++lhs_collider_index) {
    auto& lhs_collider = dynamic_colliders_[lhs_collider_index];
    handle_dymanic_collisions(lhs_collider, lhs_collider_index);
    handle_static_collisions(lhs_collider);
  }
}

void GameEngine::handle_dymanic_collisions(std::shared_ptr<DynamicBoxCollider>& lhs_collider, size_t rhs_last_index) {
  handle_collisions_range(
      lhs_collider,
      dynamic_colliders_.begin(),
      dynamic_colliders_.begin() + static_cast<ptrdiff_t>(rhs_last_index));
}

void GameEngine::handle_static_collisions(std::shared_ptr<DynamicBoxCollider>& lhs_collider) {
  handle_collisions_range(
      lhs_collider,
      static_colliders_.begin(),
      static_colliders_.end());
}

void GameEngine::remove_dead_objects() {
  remove_if(game_objects_, [] (const auto& game_object) { return game_object->is_dead(); });
  remove_if(static_colliders_, [] (const auto& game_object) { return game_object->is_dead(); });
  remove_if(dynamic_colliders_, [] (const auto& game_object) { return game_object->is_dead(); });
}

void GameEngine::draw() {
  for (auto& game_object : game_objects_) {
    game_object->draw();
  }
}

void GameEngine::register_game_object(std::shared_ptr<GameObject> game_object) {
  add_collider_if_needed(game_object);
  game_objects_.emplace_back(std::move(game_object));
}

void GameEngine::add_collider_if_needed(const std::shared_ptr<GameObject>& game_object) {
  const auto* box_collider = dynamic_cast<const BoxCollider*>(game_object.get());
  if (box_collider == nullptr) {
    return;
  }

  switch (box_collider->movement_type()) {
    case MovementType::Dynamic:
      dynamic_colliders_.emplace_back(std::static_pointer_cast<DynamicBoxCollider>(game_object));
      return;
    case MovementType::Static:
      static_colliders_.emplace_back(std::static_pointer_cast<StaticBoxCollider>(game_object));
      return;
  }
  std::clog << "unknown movement type: " << static_cast<size_t>(box_collider->movement_type());
}

} // namespace breakout
