#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "network.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ErrorLabel->setText("No error :)");
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
    //Start the game
    ui->RaceField->play();
}

void MainWindow::processVideoAndUpdateQUI()
{
    CaptureCamera.read(OriginalImageMat);

    if (OriginalImageMat.empty()) return;

    if(CamSize.height ==0 && CamSize.width == 0)
    {
        CamSize = OriginalImageMat.size();
        Processer->setCamSize(CamSize);
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
    Network n;
    n.sendData(OriginalImage);

    ui->MyVideoLabel->setPixmap(QPixmap::fromImage(n.readyRead()));
    ui->RaceField->moveCar(move);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ProcessTimer;
    delete Processer;
}

void MainWindow::closeVideoStream()
{
    ProcessTimer->stop();
    std::cout << "Video process timer stopped" <<std::endl;
    CaptureCamera.release();
    std::cout << "Camera released" <<std::endl;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Right:
            //std::cout << "Right key pressed" << std::endl;
                ui->RaceField->moveCar(1); //turn right;
            break;

        case Qt::Key_Left:
            //std::cout << "Left key pressed" << std::endl;
                ui->RaceField->moveCar(-1); //turn left;
            break;

        case Qt::Key_Escape:
            //std::cout << "Esc key pressed" << std::endl;
            closeVideoStream();
            exit(0);
            break;

        default:
            break;
    }
}
