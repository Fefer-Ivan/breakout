#include "coordinates_transform_canvas_wrapper.h"
#include "input_manager.h"
#include "box_collider.h"
#include "game_engine.h"
#include "game_object.h"
#include "timer.h"
#include <algorithm>
#include <iterator>
#include <iostream>

namespace breakout {

namespace {

constexpr Seconds kMaxTimeDelta = 0.06s;

template<typename ColliderPtr, typename ColliderIt>
void handle_collisions_range(
    ColliderPtr lhs_collider,
    ColliderIt rhs_collider_first,
    ColliderIt rhs_collider_last) {
  while (rhs_collider_first != rhs_collider_last) {
    auto& rhs_collider = *rhs_collider_first++;
    if (lhs_collider->has_collision(*rhs_collider)) {
      lhs_collider->on_collision(rhs_collider.get());
      rhs_collider->on_collision(lhs_collider);
    }
  }
}

}  // namespace

GameEngine::~GameEngine() = default;

void GameEngine::run_main_loop() {
  stopped_ = false;
  Timer timer;
  while (!stopped_ && !game_objects_.empty()) {
    auto time_delta = std::min(kMaxTimeDelta, timer.get_duration_and_restart());
    update(time_delta);
    handle_collisions();
    remove_dead_objects();
  }
}

void GameEngine::draw(Canvas* canvas) const {
  std::lock_guard<std::mutex> lock_guard(game_object_removal_mutex_);

  CoordinatesTransformCanvasWrapper game_engine_canvas(canvas, kGameFieldWidth, kGameFieldHeight);
  for (const auto& game_object : game_objects_) {
    game_object->draw(&game_engine_canvas);
  }
}

void GameEngine::update(const Seconds& time_delta) {
  for (auto& game_object : game_objects_) {
    game_object->update(time_delta);
  }
}

void GameEngine::reset() {
  std::lock_guard<std::mutex> lock_guard(game_object_removal_mutex_);
  game_objects_.clear();
  dynamic_colliders_.clear();
  static_colliders_.clear();
}

void GameEngine::handle_collisions() {
  size_t lhs_collider_index = 0;
  for (auto& lhs_collider : dynamic_colliders_) {
    handle_dynamic_collisions(lhs_collider.get(), lhs_collider_index);
    handle_static_collisions(lhs_collider.get());
    lhs_collider_index++;
  }
}

void GameEngine::handle_dynamic_collisions(DynamicBoxCollider* lhs_collider, size_t rhs_last_index) {
  handle_collisions_range(
      lhs_collider,
      dynamic_colliders_.begin(),
      std::next(dynamic_colliders_.begin(), static_cast<ptrdiff_t>(rhs_last_index)));
}

void GameEngine::handle_static_collisions(DynamicBoxCollider* lhs_collider) {
  handle_collisions_range(
      lhs_collider,
      static_colliders_.begin(),
      static_colliders_.end());
}

void GameEngine::remove_dead_objects() {
  std::lock_guard<std::mutex> lock_guard(game_object_removal_mutex_);
  game_objects_.remove_if([] (const auto& game_object) { return game_object->is_dead(); });
  static_colliders_.remove_if([] (const auto& game_object) { return game_object->is_dead(); });
  dynamic_colliders_.remove_if([] (const auto& game_object) { return game_object->is_dead(); });
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
