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
    cv::Mat readPendingDatagrams();
signals:

public slots:
    cv::Mat readyReady();
private:
    QUdpSocket *my_socket;
};

#endif // NETWORK_H
