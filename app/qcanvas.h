#pragma once
#include "canvas.h"

class QPainter;

namespace breakout {

class QCanvas : public Canvas {
public:
  QCanvas(double width, double height, QPainter* painter) :
      Canvas(width, height),
      painter_(painter) {}

  void draw_box(Vector2 center, double width, double height, Color color) override;
  void draw_text(Vector2 position, const std::string& text, Color color) override;

private:
  QPainter* painter_;

};

}  // namespace breakout