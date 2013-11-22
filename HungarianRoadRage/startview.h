#ifndef STARTVIEW_H
#define STARTVIEW_H

#include <QDialog>

namespace Ui {
class StartView;
}

class StartView : public QDialog
{
    Q_OBJECT

public:
    explicit StartView(QWidget *parent = 0);
    ~StartView();

private:
    Ui::StartView *ui;
};

#endif // STARTVIEW_H
