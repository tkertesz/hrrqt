#ifndef STARTVIEW_H
#define STARTVIEW_H

#include <QDialog>
#include <QHostAddress>
#include "mainwindow.h"

namespace Ui {
class StartView;
}

class StartView : public QDialog
{
    Q_OBJECT

public:
    explicit StartView(QWidget *parent = 0);
    StartView(QWidget *parent, MainWindow* mw);
    ~StartView();

public slots:
    void startMain();

private:
    Ui::StartView *ui;
    MainWindow* m;
};

#endif // STARTVIEW_H
