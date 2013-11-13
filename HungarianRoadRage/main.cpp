#include "mainwindow.h"
#include <QApplication>

#include <QtGui>
#include <QGraphicsView>
#include "road.h"
//using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QGraphicsView graphicView;

    QGraphicsScene *scene = new QGraphicsScene(0,0,672,942/2,&graphicView);
    graphicView.setScene(scene);
    Road* myroad = new Road;
    scene->addItem(myroad);
    //scene->addWidget();
    graphicView.show();
    w.show();
    a.exec();
    return 0;
}
