#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace breakout {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() = default;

}  // namespace breakout
