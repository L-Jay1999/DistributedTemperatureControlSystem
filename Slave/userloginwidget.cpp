#include "userloginwidget.h"
#include "ui_userloginwidget.h"

UserLoginWidget::UserLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserLoginWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    _id_input = ui->_id_input;
    _room_id_input = ui->_room_id_input;
}

UserLoginWidget::~UserLoginWidget()
{
    delete ui;
}

void UserLoginWidget::on_quitbutton_clicked()
{
    exit(0);
}

void UserLoginWidget::on_confirmbutton_clicked()
{
    qDebug() << _id_input->text();
    qDebug() << _room_id_input->text();
    SlaveControlWindow *s = new SlaveControlWindow();
    s->show();
    this->close();
}
