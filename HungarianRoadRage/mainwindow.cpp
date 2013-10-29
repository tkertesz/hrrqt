#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ErrorLabel->setText("No error :)");
    CaptureCamera.open(0);
    if(CaptureCamera.isOpened() == false)
    {
        ui->ErrorLabel->setText("Camera Error");
        std::cerr<< "Camera open error" <<std::endl;
    }
    ProcessTimer = new QTimer(this);
    connect(ProcessTimer, SIGNAL(timeout()), this, SLOT(processVideoAndUpdateQUI()));
    ProcessTimer->start(50);
}

void MainWindow::processVideoAndUpdateQUI()
{
    CaptureCamera.read(OriginalImageMat);

    if (OriginalImageMat.empty()) return;
    //Processing here :)
    cv::resize(OriginalImageMat, ResizedImageMat, cv::Size(240,150), 0, 0, cv::INTER_CUBIC);
    cv::cvtColor(ResizedImageMat, ResizedImageMat, CV_BGR2RGB);
    cv::flip(ResizedImageMat, ResizedImageMat, 1);
    QImage OriginalImage((uchar*)ResizedImageMat.data,
                         ResizedImageMat.cols,
                         ResizedImageMat.rows,
                         ResizedImageMat.step,
                         QImage::Format_RGB888);

    ui->MyVideoLabel->setPixmap(QPixmap::fromImage(OriginalImage));
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::closeVideoStream()
{
    CaptureCamera.release();
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
            exit(0);
            break;

        default:
            break;
    }
}
