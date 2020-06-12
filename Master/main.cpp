#include "standbywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StandbyWidget sw;
    sw.show();

    return a.exec();
}
