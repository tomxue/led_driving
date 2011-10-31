#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QString>

namespace Ui {
    class MainWindow;
}

class myThread : public QThread
{
  Q_OBJECT

public:
    myThread(QObject *parent = 0);
    void run();
    float duty_value;

public slots:
    void TimerUpdate();

signals:
    void deviceAmbient();

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void SliderChanged();
    void EditContentChange();
    void SetSlider();
    void CloseApp();

private:
    Ui::MainWindow *ui;
    myThread *onethread;
};


#endif // MAINWINDOW_H
