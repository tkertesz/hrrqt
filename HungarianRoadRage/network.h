#ifndef NETWORK_H
#define NETWORK_H

#include <QUdpSocket>
#include <QImage>
#include <QBuffer>
#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <iostream>

class Network : public QObject
{
        Q_OBJECT
public:
    explicit Network(QObject *parent = 0);
    ~Network();
    void sendData(QImage sendimage);

signals:
    void receivedImage(QImage q);

public slots:
    void processPendingDatagram();

private:
    QUdpSocket *my_socket;

};

#endif // NETWORK_H
