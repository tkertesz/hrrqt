#include "network.h"

Network::Network(QObject *parent) :QObject(parent)
{
    my_socket = new QUdpSocket(this);
    IsStarted = false;
}

bool Network::setIp(QHostAddress MyIP, QHostAddress OtherIP)
{
    myip = MyIP;
    otherip = OtherIP;
    return true;
}

bool Network::startBinding()
{
    if (my_socket->bind(myip, 45000))
    {
        connect(my_socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagram()));
        QCoreApplication::sendPostedEvents(); //not really necessary, but no problem :)
    }
    else
    {
        qDebug("Bind problem");
        return false;
    }

    return IsStarted = true;
}

void Network::sendData(QImage sendimage)
{
   if(IsStarted)
   {
       QByteArray q;
       QBuffer buffer(&q);
       buffer.open(QIODevice::WriteOnly);
       sendimage.save(&buffer, "JPG");
       my_socket->writeDatagram(q.data(),q.size(), otherip, 45000);
   }
   else
   {
       qDebug("Network is not started!");
       return;
   }

}

void Network::processPendingDatagram()
{

    while (my_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress sender;
        quint16 senderPort = 45000;
        datagram.resize(my_socket->pendingDatagramSize());
        my_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        //check to only allow packets from the other party, not from anyone
        if (sender.toString() == otherip.toString())
        {
        QImage recv_image;
        if (datagram.isNull())
            qDebug("Empty incoming datagram");
        recv_image.loadFromData(datagram, "JPG");

        if (recv_image.isNull())		      // Check if the image was indeed received
                qDebug("The image is null. Something failed.");
        emit receivedImage(recv_image);
        }
   }
}

Network::~Network()
{
    my_socket->close();
    delete my_socket;
}
