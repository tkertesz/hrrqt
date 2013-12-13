#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{}

void MainWindow::setIP(QHostAddress myIP, QHostAddress partnerIP)
{
    ui->setupUi(this);

    ui->ErrorLabel->setText("No error :)");

    //Camera and image processer settings
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

    ProcessTimer->start(100); //tested with QElapsedTimer, 50 was too low... it generated runtime between 60-90 msec
                              //with this we have ~12 msec :)


    //Add the graphics to graphicsview
    scene = new QGraphicsScene(0,0,Settings::SCREEN_WIDTH,Settings::SCREEN_HEIGHT,ui->graphicsView);
    ui->graphicsView->setScene(scene);

    //Other initializations
    myRoad = new Road();
    lives = Settings::STARTLIFE;
    ui->MyLifeLCD->display(lives);
    distance = 0;
    QObject::connect(myRoad, SIGNAL(sendLifeNumber(int)), this, SLOT(receiveLifeNumber(int)));
    QObject::connect(myRoad, SIGNAL(sendDistanceNumber(int)), this, SLOT(receiveDistanceNumber(int)));
    QObject::connect(myRoad, SIGNAL(stopGame()), this, SLOT(lose()));
    scene->addItem(myRoad);

    //Start the game
    QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));

    MyIpAddr=myIP;
    ui->MyIP->setText("My IP: " + MyIpAddr.toString());
    PartnerIpAddr=partnerIP;
    ui->PartnerIP->setText("Partner IP: " + PartnerIpAddr.toString());
    n = new Network();
    n->setIp(MyIpAddr,PartnerIpAddr);
    n->startBinding();
    QObject::connect(n, SIGNAL(receivedImage(QImage)), this, SLOT(receiveNetworkImage(QImage)));
    gameStarted = false;
    this->show();
}

void MainWindow::receiveLifeNumber(int i)
{
    lives = i;
    if(lives>=0) ui->MyLifeLCD->display(lives);
}

void MainWindow::receiveDistanceNumber(int i)
{
    distance = i;
    ui->MyDistLCD->display(distance);
}

void MainWindow::lose(){
    timer.stop();
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Rematch", "Would you like to restart the game?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          restart();
      } else {
          closeVideoStream();
          close();
          exit(0);
      }
}

void MainWindow::processVideoAndUpdateQUI()
{
    ProcUpdateElapsedTime.start();
    CaptureCamera.read(OriginalImageMat);

    if (OriginalImageMat.empty()) return;

    cv::resize(OriginalImageMat, ResizedImageMat, cv::Size(352,220), 0, 0, cv::INTER_CUBIC); //resizing the image to fit in the UI
    cv::flip(ResizedImageMat, ResizedImageMat, 1); //eliminating the mirror effect

    //Add the picture to the processer
    int move = Processer->getMove(ResizedImageMat);
    //std::cout << "move: " << move <<std::endl;

    //Move the car
    if(prevmove == 0)
    {
        myRoad->moveCar(move);
    }
    prevmove = move;

    cv::cvtColor(ResizedImageMat, ResizedImageMat, CV_BGR2RGB); //converting the image to RGB
    cv::rectangle(ResizedImageMat,cv::Rect(0, 0, 100, 130),cv::Scalar(200));
    cv::rectangle(ResizedImageMat,cv::Rect(250,0,102,130),cv::Scalar(200));

    QImage OriginalImage((uchar*)ResizedImageMat.data,
                         ResizedImageMat.cols,
                         ResizedImageMat.rows,
                         ResizedImageMat.step,
                         QImage::Format_RGB888); //Creating the QImage for the label
    QImage NetworkSendImage = OriginalImage;
    NetworkSendImage = NetworkSendImage.scaledToHeight(165);

    ui->MyVideoLabel->setPixmap(QPixmap::fromImage(OriginalImage));

    //Sending number of lives and distance embedded in the image
    NetworkSendImage.setText("lives", QString::number(lives));
    NetworkSendImage.setText("distance", QString::number(distance));

    n->sendData(NetworkSendImage); //sending the image over the network

//    std::cerr << "processVideoAndUpdateQUI() elapsed time: " << ProcUpdateElapsedTime.elapsed() << " msec" << std::endl << std::endl;
}

//Public slot that receives the image from the networking thread
void MainWindow::receiveNetworkImage(QImage q)
{
    if (!gameStarted)
    {
        //Start the game
        timer.start(Settings::FREQUENCY);
        gameStarted = true;
    }
    ui->NetworkCamVideo->setPixmap(QPixmap::fromImage(q)); //putting the received image to the gui
    if(q.text("lives").toInt()>=0) ui->NetworkLifeLCD->display(q.text("lives"));
    else lose();
    ui->NetworkDistLCD->display(q.text("distance"));
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
    //std::cout << "Video process timer stopped" <<std::endl;
    CaptureCamera.release();
    //std::cout << "Camera released" <<std::endl;
}

void MainWindow::restart()
{
        delete(myRoad);
        myRoad = new Road();
        lives = Settings::STARTLIFE;
        ui->MyLifeLCD->display(lives);
        distance = 0;
        ui->MyDistLCD->display(distance);
        timer.start(Settings::FREQUENCY);
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
