#include "mainwindow.h"
#include "qcanvas.h"
#include "qinputmanager.h"
#include "game_runner.h"

namespace breakout {

MainWindow::MainWindow(QWindow* parent) :
    QWindow(parent),
    backing_store_(std::make_unique<QBackingStore>(this)) {
  resize(700, 700);

  auto input_manager = std::make_unique<QInputManager>();
  input_manager_ = input_manager.get();
  game_runner_ = std::make_unique<GameRunner>(std::move(input_manager));
  game_runner_->start();
}

MainWindow::~MainWindow() = default;

bool MainWindow::event(QEvent* event) {
  if (event->type() == QEvent::UpdateRequest) {
    render_now();
    return true;
  }
  return QWindow::event(event);
}

void MainWindow::render_later() {
  requestUpdate();
}

void MainWindow::resizeEvent(QResizeEvent* resize_event) {
  backing_store_->resize(resize_event->size());
  if (isExposed()) {
    render_now();
  }
}

void MainWindow::exposeEvent(QExposeEvent*) {
  if (isExposed()) {
    render_now();
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  input_manager_->press_key(event->key());
}
void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  input_manager_->release_key(event->key());
}

void MainWindow::render_now() {
  if (!isExposed()) {
    return;
  }

  QRect rect(0, 0, width(), height());
  backing_store_->beginPaint(rect);

  QPaintDevice* device = backing_store_->paintDevice();
  QPainter painter(device);

  painter.fillRect(0, 0, width(), height(), Qt::black);
  render(&painter);
  painter.end();

  backing_store_->endPaint();
  backing_store_->flush(rect);

  render_later();
}

void MainWindow::render(QPainter* painter) {
  QCanvas canvas(width(), height(), painter);
  game_runner_->draw(&canvas);
}

}  // namespace breakout
