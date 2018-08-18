#pragma once
#include <QtGui>

namespace breakout {

class MainWindow : public QWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWindow* parent = nullptr);

	void render(QPainter* painter);

public slots:
	void render_later();
	void render_now();

protected:
	bool event(QEvent* event) override;

	void resizeEvent(QResizeEvent* event) override;
	void exposeEvent(QExposeEvent* event) override;

private:
	QBackingStore* backing_store_;
};

}  // namespace breakout
