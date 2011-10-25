#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include "gpio.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpDate()));
    timer->start(20); //20ms one time
}

void MainWindow::timerUpDate()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
                 this, SLOT(setValue(int)));
}

int MainWindow::setValue(int duty_value)
{
//	typedef void (* my_func_t) (void *addr);
	 
//	QLibrary lib("libsum.so");
//	my_func_t func = (my_func_t)lib.resolve("sum2"); // 
//	if (!func) {
//		  return -2;
//	}
//	func(8,6);	
  // gpio(duty_value);
  // sleep(1);
  return gpio(30);
  //printf("hello");
}

MainWindow::~MainWindow()
{
    delete ui;
}
