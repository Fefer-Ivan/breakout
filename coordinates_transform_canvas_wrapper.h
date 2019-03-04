#pragma once
#include "canvas.h"
#include "vector2.h"
#include <string_view>

namespace breakout {

class CoordinatesTransformCanvasWrapper : public Canvas {
public:
  explicit CoordinatesTransformCanvasWrapper(Canvas* canvas, double width, double height) :
      Canvas(width, height),
      canvas_(canvas) {}

  void draw_box(Vector2 center, double width, double height, Color color) override;
  void draw_text(Vector2 position, std::string_view text, Color color) override;

private:
  Vector2 to_screen_vector(Vector2 v) const;
  double to_screen_x(double x) const;
  double to_screen_y(double y) const;
  double to_screen_height(double height) const;

  Canvas* canvas_;
};
}  // namespace breakout
