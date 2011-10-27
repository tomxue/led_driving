#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>

extern "C" {
#include "gpio.h"
#include "sum.h"
}

#define high 1
#define low  0
#define ongoing 1
#define stop 0

/* ****** Thread part ****** */
myThread::myThread(QObject *parent)
    : QThread(parent)
{
}

void myThread::run()
{
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(TimerUpdate()));
    timer.start(100); //update of each 100ms
    exec();
}

void myThread::TimerUpdate()
{
    int i,j;
    if( (duty_value<100)&&(duty_value>0) ) 
    {
      i = duty_value;
      j = 100 - duty_value;
    }
    else
    {
      i = 50;
      j = 50;
    } 
    emit deviceAmbient();
    sum2(2,3);
    gpio(1,1);
/*
    gpio(high, ongoing);
    usleep(800*i);

    gpio(low, ongoing);
    usleep(800*j);

    gpio(low, stop);
*/
}
/* ****** Thread part ****** */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("NaN"); 
    ui->horizontalSlider->setValue(50);
    ui->horizontalSlider->show();
    
    onethread = new myThread(this);
    onethread->duty_value = 50;
    connect(onethread, SIGNAL(deviceAmbient()),
            this, SLOT(SliderChanged()));
    onethread->start(QThread::NormalPriority);
}

void MainWindow::SliderChanged()
{
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)),
                 this, SLOT(SetSlider()));
}

void MainWindow::SetSlider()
{
    onethread->duty_value = ui->horizontalSlider->value();
}

void MainWindow::CloseApp()
{
    connect(ui->pushButton, SIGNAL(clicked()),
                 this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
