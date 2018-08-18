#pragma once
#include "seconds.h"
#include <memory>
#include <vector>
#include <QColor>

namespace breakout {

class GameObject;
class DynamicBoxCollider;
class StaticBoxCollider;

class GameEngine {
public:
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

private:
  void update(const Seconds& time_delta);

  void handle_collisions();
  void handle_dymanic_collisions(std::shared_ptr<DynamicBoxCollider>& lhs_collider, size_t rhs_last_index);
  void handle_static_collisions(std::shared_ptr<DynamicBoxCollider>& lhs_collider);

  void remove_dead_objects();

  void register_game_object(std::shared_ptr<GameObject> game_object);
  void add_collider_if_needed(const std::shared_ptr<GameObject>& game_object);

  bool stopped_;
  std::vector<std::shared_ptr<GameObject>> game_objects_;
  std::vector<std::shared_ptr<DynamicBoxCollider>> dynamic_colliders_;
  std::vector<std::shared_ptr<StaticBoxCollider>> static_colliders_;
};

class GameEngineRunner : protected GameEngine {
public:
  virtual ~GameEngineRunner() = default;

  void run() {
    create_initial_game_objects();
    run_main_loop();
  }

private:
  virtual void create_initial_game_objects() = 0;
};

}  // namespace breakout
