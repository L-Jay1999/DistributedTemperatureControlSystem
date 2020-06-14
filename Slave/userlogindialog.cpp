#include "userlogindialog.h"
#include "ui_userlogindialog.h"

UserLoginDialog::UserLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    _id_input = ui->_id_input;
    _room_id_input = ui->_room_id_input;

    _listener = new Listener(parent);
    auto port = _listener->ListenOnRandomPort(1080, 1100);
    Config::setSlaveListenerPort(port);

    // connect(this, &UserLoginDialog::LoginSuccess, dynamic_cast<SlaveControlWindow*>(parent), &SlaveControlWindow::SetLoginUser);
    connect(this, SIGNAL(LoginSuccess(const QString &, const QString &, WorkingMode, double)),
            parent, SLOT(SetLoginUser(const QString &, const QString &, WorkingMode, double)));
}

UserLoginDialog::~UserLoginDialog()
{
    delete ui;
}

void UserLoginDialog::on_quitbutton_clicked()
{
    Config::clearSlaveListenerPort();
    assert(!Config::hasSlaveListenerPort());
    delete _listener;
    emit reject();
    close();
}

void UserLoginDialog::on_confirmbutton_clicked()
{
    using namespace std::chrono_literals;
    qDebug() << _id_input->text();
    qDebug() << _room_id_input->text();
    LoginController logincontroller(_id_input->text(), _room_id_input->text(), Config::getSlaveListenerPortValue());
    auto [error, is_suc, init_mode, init_temp] = logincontroller.Login();
//    auto [is_suc, err_str, init_mode, init_temp] = {true, "", WorkingMode::COLD, 25.0};
//    auto is_suc = true;
//    auto err_str = "";
//    auto init_mode = WorkingMode::COLD;
//    auto init_temp = 25.0;
    qDebug() << "111";
    if (error.hasError())
    {
        qDebug() << "222";
        QMessageBox *err_msg = new QMessageBox("登录失败", error.err_str,
                                               QMessageBox::Critical, QMessageBox::Ok,
                                               QMessageBox::NoButton, QMessageBox::NoButton,
                                               this);
        err_msg->exec();
    }
    else if(is_suc)
    {
        qDebug() << "333";
        emit LoginSuccess(_room_id_input->text(), _id_input->text(), init_mode, init_temp);
        std::this_thread::sleep_for(200ms);
        emit accept();
        this->close();
    }
    else
    {
        qDebug() << "444";
        QMessageBox *err_msg = new QMessageBox("登录失败", "身份证号或房间号错误",
                                               QMessageBox::Critical, QMessageBox::Ok,
                                               QMessageBox::NoButton, QMessageBox::NoButton,
                                               this);
        err_msg->exec();
        // log
    }
}
