#pragma once
#include "canvas.h"
#include "seconds.h"
#include "vector2.h"
#include <list>
#include <memory>
#include <mutex>
#include <vector>

namespace breakout {

class GameObject;
class DynamicBoxCollider;
class StaticBoxCollider;
class Canvas;

class GameEngine {
public:
  GameEngine() : stopped_(false) {}
  ~GameEngine();

  void stop() {
    stopped_ = true;
  }

  template<typename T, typename... Args>
  std::shared_ptr<T> create_game_object(Args&&... args) {
    auto game_object = std::make_shared<T>(this, std::forward<Args>(args)...);
    register_game_object(game_object);
    return game_object;
  }

protected:
  void run_main_loop();
  void draw(Canvas * canvas) const;
  void reset();

private:
  static constexpr double kGameFieldWidth = 100;
  static constexpr double kGameFieldHeight = 100;

  class CoordinatesTransformCanvasWrapper : public Canvas {
  public:
    CoordinatesTransformCanvasWrapper(Canvas* canvas) :
        Canvas(kGameFieldWidth, kGameFieldHeight),
        canvas_(canvas) {}

    void draw_box(Vector2 center, double width, double height, Color color) override;
    void draw_text(Vector2 position, const std::string& text, Color color) override;

  private:
    Vector2 to_screen_vector(Vector2 v) const;
    double to_screen_width(double height) const;
    double to_screen_height(double width) const;

    Canvas* canvas_;
  };

  void update(const Seconds& time_delta);

  void handle_collisions();
  void handle_dynamic_collisions(std::shared_ptr<DynamicBoxCollider>& lhs_collider, size_t rhs_last_index);
  void handle_static_collisions(std::shared_ptr<DynamicBoxCollider>& lhs_collider);

  void remove_dead_objects();

  void register_game_object(std::shared_ptr<GameObject> game_object);
  void add_collider_if_needed(const std::shared_ptr<GameObject>& game_object);

  bool stopped_;
  std::list<std::shared_ptr<GameObject>> game_objects_;
  std::list<std::shared_ptr<DynamicBoxCollider>> dynamic_colliders_;
  std::list<std::shared_ptr<StaticBoxCollider>> static_colliders_;
  mutable std::mutex game_object_removal_mutex_;
};

class GameEngineRunner : protected GameEngine {
public:
  virtual ~GameEngineRunner() = default;

  void run_main_loop() {
    create_initial_game_objects();
    GameEngine::run_main_loop();
  }

  void draw(Canvas* canvas) const {
    GameEngine::draw(canvas);
  }

  void reset() {
    GameEngine::reset();
  }

private:
  virtual void create_initial_game_objects() = 0;
};

}  // namespace breakout
