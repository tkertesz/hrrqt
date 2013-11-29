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
    bool setIp(QHostAddress MyIP, QString OtherIP);
    bool Network::startBinding();
    void sendData(QImage sendimage);

signals:
    void receivedImage(QImage q);

public slots:
    void processPendingDatagram();

private:
    bool IsStarted;
    QHostAddress myip;
    QHostAddress otherip;
    QUdpSocket *my_socket;

};

#endif // NETWORK_H
