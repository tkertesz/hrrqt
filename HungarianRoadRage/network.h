#ifndef NETWORK_H
#define NETWORK_H

#include <QUdpSocket>
#include <QImage>
#include <QBuffer>
#include <QObject>
#include <iostream>
#include "debugwindow.h"

class Network : public QObject
{
        Q_OBJECT
public:
    explicit Network(QObject *parent = 0);
    ~Network();
    void sendData(QImage image);
signals:

public slots:
    void processPendingDatagram();
    QImage get_image();
private:
    QUdpSocket *my_socket;
    QImage image;
    DebugWindow NetworkDebugWin;
};

#endif // NETWORK_H
