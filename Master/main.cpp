#include "mainwindow.h"

#include <QApplication>

#include "../include/common.h"
//#include "../include/listener.h"
//#include "../include/request_base.h"
//#include "../include/request_controller.h"
//#include "../include/request_payload.h"
//#include "../include/requests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() <<
    w.show();
    return a.exec();
}
