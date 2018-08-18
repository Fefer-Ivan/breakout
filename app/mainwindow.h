#pragma once
#include <QtGui>
#include <memory>

namespace breakout {

class GameRunner;

class MainWindow : public QWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWindow* parent = nullptr);
  ~MainWindow();

	void render(QPainter* painter);

public slots:
	void render_later();
	void render_now();

protected:
	bool event(QEvent* event) override;

	void resizeEvent(QResizeEvent* event) override;
	void exposeEvent(QExposeEvent* event) override;

private:
  std::unique_ptr<QBackingStore> backing_store_;
  std::unique_ptr<GameRunner> game_runner_;
};

}  // namespace breakout
