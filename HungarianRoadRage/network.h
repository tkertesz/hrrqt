#ifndef NETWORK_H
#define NETWORK_H

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
    //QImage readPendingDatagrams();
signals:

public slots:
    QImage readyRead();
private:
    QUdpSocket *my_socket;
};

#endif // NETWORK_H
