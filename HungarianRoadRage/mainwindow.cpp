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
    switch (event->key())
    {
        case Qt::Key_Right:
            //std::cout << "Right key pressed" << std::endl;
                ui->RaceField->moveCar(1); //turn right;
            break;

        case Qt::Key_Left:
            //std::cout << "Left key pressed" << std::endl;
                ui->RaceField->moveCar(-1); //turn left;
            break;

        case Qt::Key_Escape:
            //std::cout << "Esc key pressed" << std::endl;
            exit(0);
            break;

        default:
            break;
    }
}
