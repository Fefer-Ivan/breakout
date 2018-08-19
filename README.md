### The Game

Simple Breakout game prototype.

The player control the white pad with A/D and left/right arrow keys.

White balls (a little squarely balls) fly around and destroy bricks on contact. If white ball reaches bottom of the screen, it is destroyed. 
If the last white ball is destroyed, player loses one life and a new ball is created. When no lifes left the game is restarted.

The goal is to earn as many points as possible by destroying bricks. 
* Green bricks cost 10 points.
* Yellow bricks cost 20 points.
* Red bricks cost 50 points.

Darker bricks spawn pickups when destroyed. Pickups can be picked up with the pad.
* Green pickup gives 100 poins.
* Yellow pickup gives extra life.
* Red pickup spawns new white ball.

When all bricks are destroyed, game is restarted, but player keeps his score and lifes.


### The Engine

The game engine library is written on C++17 without using any external libraries.
The application is written using Qt, but it is completly isolated from the engine with interfaces.
The tests are written using gtest library.

Code files from basic to more complex:

* seconds.h - Seconds - std::chrono::duration template specialization, used across the engine.

* timer.h - Timer class for measuring time between updates.

* vector2.h - Vector class representing 2d vector or point.

* canvas.h - Canvas interface for rendering game objects

* input_manager.h - InputManager interface for getting input from user.

* game_object.h - interface for a basic game object. Has update(Seconds time_delta), draw(), on_death() and kill() virtual methods. 

* box_collider.h - BoxCollider class, derived from GameObject, responsable for detecting collisions. Has on_collision() virtual method.

* game_objects/ directory - contains various game objects: ball, player pad, bricks, pickups. One relativly special game object is GameManager which stores player lifes and score.

* game_engine.h - THE game engine class. Responsable for the game main loop.
    While the game is not stopped:
    1. Call update function for all GameObjects.
    2. Check for collisions and call on_collision.
    3. Remove killed game objects.

* game_runner.h - Class that initializes game objects, forming the only level of the game, and starts the engine.

* app/ directory contains Qt application with the game. It has QCanvas - implementation of Canvas interface and QInputManager - implementation of InputManager interface.

* tests/ directory contains unit tests for basic classes, game objects and a couple simple tests for game engine.

### Comments

There are a lot room for improvements:
1. As all colliders are squares that are parallel to the axis, collision detection can be optimized.
2. Support continious collision detection for fast objects.
3. Support collision masks: simple way to specify what collisions should be ignored.
4. Now all "physics" is written in Projectile class as it is the only class that need it. It can be generalized and put into separate class.
5. Test coverage can be improved. Now only basic classes are covered. 
