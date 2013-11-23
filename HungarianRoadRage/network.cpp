#include "network.h"

Network::Network(QObject *parent) :QObject(parent)
{
    my_socket = new QUdpSocket(this);
    if (my_socket->bind(QHostAddress::LocalHost, 45000))
    {
        connect(my_socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagram()));
        QCoreApplication::sendPostedEvents(); //not really necessary, but no problem :)
    }
    else
        qDebug("Bind problem");
}


//Domi, mi lenne ha itt adnank meg neki, hogy mit akarunk beleirni???
void Network::sendData(QImage sendimage)
{
   QByteArray q;
   QBuffer buffer(&q);
   buffer.open(QIODevice::WriteOnly);
   sendimage.save(&buffer, "JPG");
   my_socket->writeDatagram(q.data(),q.size(), QHostAddress::LocalHost, 45000);
}

void Network::processPendingDatagram()
{

    while (my_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress sender;
        quint16 senderPort = 45000;
        datagram.resize(my_socket->pendingDatagramSize());
//Domi itt majd a senderPort-ot meg a sendert beallitjuk a masik IP-re es akkor nem lesz beleszolas mashonnan :)
        my_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QImage recv_image;
        if (datagram.isNull())
            qDebug("Empty incoming datagram");
        recv_image.loadFromData(datagram, "JPG");

        if (recv_image.isNull())		      // Check if the image was indeed received
                qDebug("The image is null. Something failed.");
        emit receivedImage(recv_image);
   }
}

Network::~Network()
{
    my_socket->close();
    delete my_socket;
}
