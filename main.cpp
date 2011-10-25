#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QtCore>
//#include "sum.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //qDebug() << sum2(8,7);
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
