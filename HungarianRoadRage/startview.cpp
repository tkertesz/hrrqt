#include "mainwindow.h"
#include "startview.h"
#include "ui_startview.h"
#include <QNetworkInterface>
#include <QMessageBox>

void StartView::startMain(){
    QString p = ui->partnerIP->text();
    QHostAddress me(ui->myIPlist->currentText());
    QHostAddress partner;
    if (p.isEmpty())
        partner = me;
    else
        partner = QHostAddress(p);
    if (partner.protocol() != QAbstractSocket::IPv4Protocol) {
        QMessageBox mb;
        mb.setText("Invalid IP address");
        mb.exec();
        exit(QDialog::Rejected);
    } else {
        m->setIP(me, partner);
    }
}

StartView::StartView(QWidget *parent, MainWindow* mw) :
    QDialog(parent),
    ui(new Ui::StartView)
{
    ui->setupUi(this);
    ui->helpText->setText("This program is brought to you by Feli, Domi and Tibby\n\nIf you don't have a partner to play with just leave the Partner IP-address field empty.\n\n\nObjective of the game: using your left and right hand (or probably any other body part, your friend, your cat, your potato, your microwave, the bus you ride to get to work etc.) control your car through the horrible roads of Hungary and avoid the potholes to keep your car and your passengers safe.");
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
