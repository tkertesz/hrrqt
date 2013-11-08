#include "network.h"

Network::Network(QObject *parent) :QObject(parent)
{
    my_socket = new QUdpSocket(this);
    my_socket->bind(QHostAddress::LocalHost, 1337);
    connect(my_socket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagram()));
}

void Network::sendData(QImage image)
{
    QByteArray q;
    QBuffer buffer(&q);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer);
    my_socket->writeDatagram(q, QHostAddress::LocalHost, 1337);
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
        QImage recv_image((uchar*)datagram.data(), 240, 150, QImage::Format_RGB888);
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
