#include "coordinates_transform_canvas_wrapper.h"

namespace breakout {

void CoordinatesTransformCanvasWrapper::draw_box(
    Vector2 center,
    double width,
    double height,
    Color color) {
  canvas_->draw_box(
      to_screen_vector(center),
      to_screen_x(width),
      to_screen_height(height),
      color);
}

void CoordinatesTransformCanvasWrapper::draw_text(
    Vector2 position,
    const std::string& text,
    Color color) {
  canvas_->draw_text(to_screen_vector(position), text, color);
}

Vector2 CoordinatesTransformCanvasWrapper::to_screen_vector(Vector2 v) const {
  return Vector2(to_screen_x(v.x()), to_screen_y(v.y()));
}

double CoordinatesTransformCanvasWrapper::to_screen_x(double x) const {
  return x / width() * canvas_->width();
}

double CoordinatesTransformCanvasWrapper::to_screen_y(double y) const {
  return (height() - y) / height() * canvas_->height();
}

double CoordinatesTransformCanvasWrapper::to_screen_height(double engine_height) const {
  return engine_height / height() * canvas_->height();
}

}  // namespace breakout

