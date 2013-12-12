#include "mainwindow.h"
#include "startview.h"
#include "ui_startview.h"
#include <QNetworkInterface>
#include <QMessageBox>

void StartView::startMain(){
    QHostAddress partner(ui->partnerIP->text());
    QHostAddress me(ui->myIPlist->currentText());
    if (partner.protocol() != QAbstractSocket::IPv4Protocol) {
        QMessageBox mb;
        mb.setText("Invalid IP address");
        mb.exec();
    } else {
        m->setIP(me, partner);
    }
}

StartView::StartView(QWidget *parent, MainWindow* mw) :
    QDialog(parent),
    ui(new Ui::StartView)
{
    ui->setupUi(this);
    m = mw;
    QList<QHostAddress> list=QNetworkInterface::allAddresses();
    QString str;
    for (int i = 0; i < list.size(); ++i) {
        if (!(list.at(i).toString().contains("::")) && !(list.at(i).toString().contains("169"))){
            ui->myIPlist->addItem(list.at(i).toString());
        }
    }
    connect(this, SIGNAL(accepted()), SLOT(startMain()));
}



StartView::~StartView()
{
    delete ui;
}
