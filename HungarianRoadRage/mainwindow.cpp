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

    ///Add the graphics to graphicsview
    scene = new QGraphicsScene(0,0,Settings::ROAD_WIDTH,Settings::SCREEN_HEIGHT,ui->graphicsView);
    ui->graphicsView->setScene(scene);
    myCar = new Car;
    myRoad = new Road(myCar);
    scene->addItem(myRoad);
    scene->addItem(myCar);

    ProcessTimer->start(50);
    ///Start the game
    myRoad->setFocus();
    timer.start(1000,this);
    timer2.start(30,this);
    NetworkStarted =  false;
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
        NetworkStarted = true;
    }

    int move = Processer->getMove(OriginalImageMat);
    std::cout << "move: " << move <<std::endl;

    cv::resize(OriginalImageMat, ResizedImageMat, cv::Size(240,150), 0, 0, cv::INTER_CUBIC);
    cv::cvtColor(ResizedImageMat, ResizedImageMat, CV_BGR2RGB);
    cv::flip(ResizedImageMat, ResizedImageMat, 1);
    QImage OriginalImage((uchar*)ResizedImageMat.data,
                         ResizedImageMat.cols,
                         ResizedImageMat.rows,
                         ResizedImageMat.step,
                         QImage::Format_RGB888);

    //QImage debug = QImage("debug/images/kep.png").scaledToHeight(240).scaledToHeight(150);

    n->sendData(OriginalImage);
    NetworkImage = n->get_image();
    ui->MyVideoLabel->setPixmap(QPixmap::fromImage(OriginalImage));
    ui->NetworkCamVideo->setPixmap(QPixmap::fromImage(NetworkImage));

    ///Move car
    //myRoad->moveCar(move);
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

void MainWindow::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timer.timerId()) {
        if(myRoad->isHit()){
            if(myRoad->decreaseLife()<1)
            {
                closeVideoStream();
                close();
                exit(0);
            }
        }
        myRoad->represent();
    } else if(event->timerId() == timer2.timerId()){
        myRoad->roadStep();
        myRoad->represent();
    }else{
        QWidget::timerEvent(event);
    }
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
