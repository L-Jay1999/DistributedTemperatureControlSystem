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

    Listener *listener = new Listener(this);
    _port = listener->ListenOnRandomPort(1080, 1100);
    Config::setSlaveListenerPort(_port);
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
//    LoginController *logincontroller = new LoginController(_id_input->text(), _room_id_input->text(), _port);
//    std::tuple<bool, QString, WorkingMode, double>result = logincontroller->Login();
//    if(std::get<0>(result)){
//        SlaveControlWindow *s = new SlaveControlWindow();
//        User *user = new User(_room_id_input, _id_input);
//        s->setUser(user);
//        s->show();
//        this->close();
//    }
//    else{
//        qDebug() << std::get<1>(result);
//    }
    SlaveControlWindow *s = new SlaveControlWindow();
    User *user = new User(_room_id_input->text(), _id_input->text());
    s->setUser(user);
    s->show();
    this->close();
}
