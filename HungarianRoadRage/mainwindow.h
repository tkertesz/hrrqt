#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //Handling the key press events
    void keyPressEvent(QKeyEvent *);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
