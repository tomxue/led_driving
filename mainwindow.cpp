#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>

extern "C" {
#include "pwm_test.h"
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
    timer.start(200); //update of each 200ms
    exec();
}

void myThread::TimerUpdate()
{

    emit deviceAmbient();
    pwm_test(duty_value/10.0);

}
/* ****** Thread part ****** */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("NaN"); 
    ui->horizontalSlider->setValue(500);
    ui->horizontalSlider->show();
    
    onethread = new myThread(this);
    onethread->duty_value = 500;
    connect(onethread, SIGNAL(deviceAmbient()),
            this, SLOT(SliderChanged()));
    connect(onethread, SIGNAL(deviceAmbient()),
            this, SLOT(EditContentChange()));
    onethread->start(QThread::NormalPriority);
    connect(ui->pushButton, SIGNAL(clicked()),
            this, SLOT(CloseApp()));
}

void MainWindow::SliderChanged()
{
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)),
                 this, SLOT(SetSlider()));
}

void MainWindow::EditContentChange()
{
    float duty;
    QString s;
    duty = onethread->duty_value/10.0;
    s.sprintf("%.2f", duty);
    ui->lineEdit->setText(s);
 // ui->lineEdit->setText("the duty cycle");
}

void MainWindow::SetSlider()
{
    onethread->duty_value = ui->horizontalSlider->value();
}

void MainWindow::CloseApp()
{
    close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
