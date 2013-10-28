#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event ->key() == Qt::Key_Left) {
        std::cout << "Left key pressed" << std::endl;
        return;
    }
    else if (event->key() == Qt::Key_Right) {
        std::cout << "Right key pressed" << std::endl;
        return;
    }
    else if (event->key() == Qt::Key_Escape) {
        std::cout << "Esc key pressed" << std::endl;
        return;
    }
}
