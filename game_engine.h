#pragma once
#include "seconds.h"
#include <memory>
#include <vector>

namespace breakout {

class GameObject;
class DynamicBoxCollider;
class StaticBoxCollider;

class GameEngine {
public:
  GameEngine(std::vector<std::shared_ptr<GameObject>> game_objects);
  ~GameEngine();

  void run_main_loop();

  void stop() {
    stopped_ = true;
  }

  template<typename T, typename... Args>
  void spawn_game_object(Args&&... args) {
    spawn_game_object(std::make_shared<T>(std::forward<Args>(args)...));
  }

private:
  void update(const Seconds& time_delta);

  void handle_collisions();
  void handle_dymanic_collisions(std::shared_ptr<DynamicBoxCollider>& lhs_collider, size_t rhs_last_index);
  void handle_static_collisions(std::shared_ptr<DynamicBoxCollider>& lhs_collider);

  void remove_dead_objects();

  void draw();

  void spawn_game_object(std::shared_ptr<GameObject> game_object);
  void add_collider_if_needed(const std::shared_ptr<GameObject>& game_object);

  bool stopped_;
  std::vector<std::shared_ptr<GameObject>> game_objects_;
  std::vector<std::shared_ptr<DynamicBoxCollider>> dynamic_colliders_;
  std::vector<std::shared_ptr<StaticBoxCollider>> static_colliders_;
};

}  // namespace breakout
