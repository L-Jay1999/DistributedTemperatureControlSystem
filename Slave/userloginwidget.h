#ifndef USERLOGINWIDGET_H
#define USERLOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QDebug>
#include "slavecontrolwindow.h"

namespace Ui {
class UserLoginWidget;
}

class UserLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserLoginWidget(QWidget *parent = 0);
    ~UserLoginWidget();

private slots:
    void on_quitbutton_clicked();

    void on_confirmbutton_clicked();

private:
    Ui::UserLoginWidget *ui;
    QLineEdit *_id_input;
    QLineEdit *_room_id_input;

};

#endif // USERLOGINWIDGET_H
