#pragma once
#include <string>
#include <utility>

namespace breakout {

enum class CommandType {
  Box,
  Text
};

enum class Color {
  White,
  Green,
  Yellow,
  Red
};

class DrawCommand {
public:
  virtual ~DrawCommand() = default;

  CommandType type() const {
    return type_;
  }

  int x() const {
    return x_;
  }

  int y() const {
    return y_;
  }

protected:
  DrawCommand(CommandType type, int x, int y) : type_(type), x_(x), y_(y) {}

private:
  CommandType type_;
  int x_;
  int y_;
};

class DrawBoxCommand : public DrawCommand {
public:
  DrawBoxCommand(int x, int y, int width, int height, Color color) :
      DrawCommand(Box, x, y), width_(width), height_(height), color_(color) {}

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

  Color color() const {
    return color_;
  }

private:
  int width_;
  int height_;
  Color color;
}

class DrawTextCommand : public DrawCommand {
public:
  DrawTextCommand(int x, int y, std::string text) :
      DrawCommand(CommandType::Text, x, y), text_(std::move(text)) {}

  const std::string& text() const {
    return text;
  }

private:
  std::string text_;
}

}  // namespace breakout
