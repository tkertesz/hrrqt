#include "startview.h"
#include "ui_startview.h"

StartView::StartView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartView)
{
    ui->setupUi(this);
}

StartView::~StartView()
{
    delete ui;
}
