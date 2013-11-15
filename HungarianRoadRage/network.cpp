#include "network.h"
#include <QDebug>

Network::Network(QObject *parent) :QObject(parent)
{
    my_socket = new QUdpSocket(this);
    //my_socket->bind(QHostAddress::LocalHost, 1337);
    my_socket->bind(QHostAddress("192.168.254.98"), 1337);
    connect(my_socket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagram()));
}

void Network::sendData(QImage image)
{
    QByteArray q;
    QBuffer buffer(&q);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    //my_socket->writeDatagram(q, QHostAddress::LocalHost, 1337);
    my_socket->writeDatagram(q, QHostAddress("192.168.254.108"), 1337);
    std::cerr << QHostAddress::LocalHost <<std::endl;
}

void Network::processPendingDatagram()
{

    while (my_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(my_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        my_socket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        //QImage recv_image((uchar*)datagram.data(), 240, 150, QImage::Format_RGB888);
        QImage recv_image;
        if (datagram.isNull())
            qDebug("Ures a bejovo buzi!!");
        else
            qDebug("datagram nem ures");
        recv_image.loadFromData(datagram, "PNG");

        if (recv_image.isNull())		      // Check if the image was indeed received
                qDebug("The image is null. Something failed.");
        image = recv_image;
   }
    //image = QImage("debug/images/kep.png").scaledToHeight(240).scaledToHeight(150);
}

QImage Network::get_image()
{
    return image;
}

Network::~Network()
{
    delete my_socket;
}
