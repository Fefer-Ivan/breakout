#pragma once
#include "vector2.h"
#include <string>

namespace breakout {

enum class Color {
  White,
  Green,
  DarkGreen,
  Yellow,
  DarkYellow,
  Red,
  DarkRed
};

class Canvas {
public:
  Canvas(double width, double height) : width_(width), height_(height) {}

  double width() const {
    return width_;
  }

  double height() const {
    return height_;
  }

  virtual void draw_box(Vector2 center, double width, double height, Color color) = 0;
  virtual void draw_text(Vector2 position, const std::string& text, Color color) = 0;

private:
  double width_;
  double height_;
};

}  // namespace breakout
