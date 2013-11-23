#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ErrorLabel->setText("No error :)");

    foreach(const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             MyIpAddr = address.toString();
    }
    ui->MyIP->setText("My ip: " + MyIpAddr);

    CaptureCamera.open(0);
    if(CaptureCamera.isOpened() == false)
    {
        ui->ErrorLabel->setText("Camera Error");
        std::cerr<< "Camera open error" <<std::endl;
    }

    CamSize = OriginalImageMat.size();
    Processer = new ImageProcesser(CamSize);
    ProcessTimer = new QTimer(this);
    connect(ProcessTimer, SIGNAL(timeout()), this, SLOT(processVideoAndUpdateQUI()));

    ProcessTimer->start(50);

    ///Add the graphics to graphicsview
    scene = new QGraphicsScene(0,0,Settings::SCREEN_WIDTH,Settings::SCREEN_HEIGHT,ui->graphicsView);
    ui->graphicsView->setScene(scene);
    myRoad = new Road();
    ui->MyLifeLCD->display(Settings::STARTLIFE);
    QObject::connect(myRoad, SIGNAL(sendLifeNumber(int)), this, SLOT(receiveLifeNumber(int)));
    QObject::connect(myRoad, SIGNAL(sendDistanceNumber(int)), this, SLOT(receiveDistanceNumber(int)));
    scene->addItem(myRoad);

    ///Start the game
    QObject::connect(&timer, SIGNAL(timeout()),scene, SLOT(advance()));
    timer.start(Settings::FREQUENCY);
    NetworkStarted =  false;
}

void MainWindow::receiveLifeNumber(int i)
{
    lives = i;
    ui->MyLifeLCD->display(lives);
}

void MainWindow::receiveDistanceNumber(int i)
{
    distance = i;
    ui->MyDistLCD->display(distance);
}
void MainWindow::processVideoAndUpdateQUI()
{
    CaptureCamera.read(OriginalImageMat);

    if (OriginalImageMat.empty()) return;

    if(CamSize.height == 0)
    {
        CamSize = OriginalImageMat.size();
        Processer->setCamSize(CamSize);
    }
    if(!NetworkStarted)
    {
        n = new Network();
        QObject::connect(n, SIGNAL(receivedImage(QImage)), this, SLOT(receiveNetworkImage(QImage)));
        NetworkStarted = true;
    }

    //int move = Processer->getMove(OriginalImageMat);
    //std::cout << "move: " << move <<std::endl;
//240,150
    cv::resize(OriginalImageMat, ResizedImageMat, cv::Size(352,220), 0, 0, cv::INTER_CUBIC); //resizing the image to fit in the UI
    cv::cvtColor(ResizedImageMat, ResizedImageMat, CV_BGR2RGB); //converting the image to RGB
    cv::flip(ResizedImageMat, ResizedImageMat, 1); //eliminating the mirror effect

    QImage OriginalImage((uchar*)ResizedImageMat.data,
                         ResizedImageMat.cols,
                         ResizedImageMat.rows,
                         ResizedImageMat.step,
                         QImage::Format_RGB888); //Creating the QImage for the label
    QImage NetworkSendImage = OriginalImage;

    ui->MyVideoLabel->setPixmap(QPixmap::fromImage(OriginalImage));

    n->sendData(NetworkSendImage); //sending the image over the network

    ///Move car
    //myRoad->moveCar(move);
}

///Public slot that receives the image from the networking thread
void MainWindow::receiveNetworkImage(QImage q)
{
    ui->NetworkCamVideo->setPixmap(QPixmap::fromImage(q)); //putting the received image to the gui
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ProcessTimer;
    delete Processer;
    delete n;
    delete scene;
    delete myCar;
    delete myRoad;
}

void MainWindow::closeVideoStream()
{
    ProcessTimer->stop();
    std::cout << "Video process timer stopped" <<std::endl;
    CaptureCamera.release();
    std::cout << "Camera released" <<std::endl;
}

// Kezeli a billentyűlenyomást
void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key())
    {
        case Qt::Key_Right:
                myRoad->moveCar(1); //turn right;
            break;
        case Qt::Key_Left:
                myRoad->moveCar(-1); //turn left;
            break;
        case Qt::Key_Escape:
            closeVideoStream();
            close();
            exit(0);
            break;
        default:
            break;
    }
}
