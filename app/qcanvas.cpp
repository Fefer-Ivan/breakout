#include "qcanvas.h"
#include <QtGui>

namespace breakout {

namespace {

QColor to_qcolor(Color color) {
  switch(color) {
    case Color::White:
      return Qt::white;
    case Color::Green:
      return Qt::green;
    case Color::DarkGreen:
      return Qt::darkGreen;
    case Color::Yellow:
      return Qt::yellow;
    case Color::DarkYellow:
      return Qt::darkYellow;
    case Color::Red:
      return Qt::red;
    case Color::DarkRed:
      return Qt::darkRed;
  }
}

}  // namespace

void QCanvas::draw_box(Vector2 center, double width, double height, Color color) {
  auto qcolor = to_qcolor(color);
  painter_->setPen(qcolor);
  painter_->setBrush(QBrush(qcolor, Qt::SolidPattern));
  painter_->drawRect(
      static_cast<int>(center.x() - width / 2),
      static_cast<int>(center.y() - height / 2),
      static_cast<int>(width),
      static_cast<int>(height));
}

void QCanvas::draw_text(Vector2 position, const std::string& text, Color color) {
  painter_->setPen(to_qcolor(color));
  painter_->drawText(
      static_cast<int>(position.x()),
      static_cast<int>(position.y()),
      QString::fromStdString(text));
}


}  // namespace breakout
