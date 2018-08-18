#pragma once
#include <QMainWindow>
#include <memory>

namespace Ui {

class MainWindow;

}  // namespace Ui

namespace breakout {

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<Ui::MainWindow> ui;
};

}  // namespace breakout
