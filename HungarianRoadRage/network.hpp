#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <opencv2/imgproc/imgproc.hpp>
#include <QUdpSocket>
#include <QImage>
#include <QBuffer>
#include <QObject>
#include <opencv2/highgui/highgui.hpp>

class Network : public QObject
{
        Q_OBJECT
public:
    explicit Network(QObject *parent = 0);
    void sendData(QImage image);
    cv::Mat readPendingDatagrams();
signals:

public slots:
    cv::Mat readyReady();
private:
    QUdpSocket *my_socket;
};


Network::Network(QObject *parent) :QObject(parent)
{
    my_socket = new QUdpSocket(this);
    my_socket->bind(QHostAddress::LocalHost, 1337);
    connect(my_socket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
};

void Network::sendData(QImage image)
{
    QByteArray q;
    QBuffer buffer(&q);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    my_socket->writeDatagram(q, QHostAddress::LocalHost, 1337);
};

cv::Mat Network::readyReady()
{

    while (my_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(my_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        my_socket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        cv::Mat recvImg = cv::Mat(400, 300, CV_8UC3, &datagram);
        return recvImg;
   }
};

#endif // NETWORK_HPP
