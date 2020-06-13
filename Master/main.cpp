#include "standbywidget.h"
#include <QApplication>

#include "../CommonLib/common.h"

int main(int argc, char *argv[])
{
    Config::setUserType(Config::UserType::MASTER);
    QApplication a(argc, argv);
    StandbyWidget sw;
    sw.show();
    return a.exec();
}
