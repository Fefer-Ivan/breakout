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
  }
}

void GameEngine::draw(Canvas* canvas) const {
  std::lock_guard<std::mutex> lock_guard(draw_reset_mutex_);

  CoordinatesTransformCanvasWrapper game_engine_canvas(canvas);
  for (const auto& game_object : game_objects_) {
    game_object->draw(&game_engine_canvas);
  }
}

void GameEngine::CoordinatesTransformCanvasWrapper::draw_box(
    Vector2 center,
    double width,
    double height,
    Color color) {
  canvas_->draw_box(
      to_screen_vector(center),
      to_screen_width(width),
      to_screen_height(height),
      color);
}

void GameEngine::CoordinatesTransformCanvasWrapper::draw_text(
    Vector2 position,
    const std::string& text,
    Color color) {
  canvas_->draw_text(to_screen_vector(position), text, color);
}

Vector2 GameEngine::CoordinatesTransformCanvasWrapper::to_screen_vector(Vector2 v) const {
  return Vector2(
    v.x() / kGameFieldWidth * canvas_->width(),
    (kGameFieldHeight - v.y()) / kGameFieldHeight * canvas_->height());
}

double GameEngine::CoordinatesTransformCanvasWrapper::to_screen_width(double engine_width) const {
  return engine_width / kGameFieldWidth * canvas_->width();
}

double GameEngine::CoordinatesTransformCanvasWrapper::to_screen_height(double engine_height) const {
  return engine_height / kGameFieldHeight * canvas_->height();
}

void GameEngine::update(const Seconds& time_delta) {
  for (auto& game_object : game_objects_) {
    game_object->update(time_delta);
  }
}

void GameEngine::reset() {
  std::lock_guard<std::mutex> lock_guard(draw_reset_mutex_);

  game_objects_.clear();
  dynamic_colliders_.clear();
  static_colliders_.clear();
}

void GameEngine::handle_collisions() {
  for (size_t lhs_collider_index = 0; lhs_collider_index < dynamic_colliders_.size(); ++lhs_collider_index) {
    auto& lhs_collider = dynamic_colliders_[lhs_collider_index];
    handle_dynamic_collisions(lhs_collider, lhs_collider_index);
    handle_static_collisions(lhs_collider);
  }
}

void GameEngine::handle_dynamic_collisions(std::shared_ptr<DynamicBoxCollider>& lhs_collider, size_t rhs_last_index) {
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
  game_objects_.remove_if([] (const auto& game_object) { return game_object->is_dead(); });
  remove_if(static_colliders_, [] (const auto& game_object) { return game_object->is_dead(); });
  remove_if(dynamic_colliders_, [] (const auto& game_object) { return game_object->is_dead(); });
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
