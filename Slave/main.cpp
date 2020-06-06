#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "../CommonLib/common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() << Config::kRetryAttempt;
    w.show();
    return a.exec();
}
