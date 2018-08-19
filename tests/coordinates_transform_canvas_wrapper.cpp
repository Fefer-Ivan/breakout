#include "coordinates_transform_canvas_wrapper.h"
#include "canvas.h"
#include <gtest/gtest.h>

namespace breakout {

namespace {

class TestCanvas : public Canvas {
public:
  TestCanvas(
      double width,
      double height,
      Vector2 expected_center,
      double expected_width,
      double expected_height) :
          Canvas(width, height),
          expected_center_(expected_center),
          expected_width_(expected_width),
          expected_height_(expected_height) {}

  void draw_box(Vector2 center, double width, double height, Color /*color*/) override {
    EXPECT_EQ(center, expected_center_);
    EXPECT_EQ(width, expected_width_);
    EXPECT_EQ(height, expected_height_);
  }

  void draw_text(Vector2 position, const std::string& /*text*/, Color /*color*/) override {
    EXPECT_EQ(position, expected_center_);
  }

private:
  Vector2 expected_center_;
  double expected_width_;
  double expected_height_;
};

}  // namespace

TEST(CoordinatesTransformCanvasWrapper, Draw) {
  TestCanvas canvas(1000, 500, Vector2(100, 50), 200, 250);
  CoordinatesTransformCanvasWrapper wrapper(&canvas, 100, 50);
  wrapper.draw_box(Vector2(10, 45), 20, 25, Color::White);
  wrapper.draw_text(Vector2(10, 45), "test", Color::White);
}

}  // namespace breakout
