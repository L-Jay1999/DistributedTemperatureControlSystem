#include "standbywidget.h"
#include <QApplication>
#include <QTextCodec>
#include<QDebug>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));
    StandbyWidget sw;
    sw.show();
    return a.exec();
}
