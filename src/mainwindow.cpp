#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include <random>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_actionCreateRect_triggered()
{
    fmt::print("on_actionCreateRect_triggered\n");
    float dx = rand() % 200 / 100.0f - 1.0f;
    float dy = rand() % 200 / 100.0f - 1.0f;
    ui->openGLWidget->setNewRect(dx, dy, 0);
}

void MainWindow::on_actionClearAllRects_triggered()
{
    fmt::print("on_actionClearAllRects_triggered\n");
    ui->openGLWidget->cleanAllRects();
    
}
