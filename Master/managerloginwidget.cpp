#include "managerloginwidget.h"
#include "ui_managerloginwidget.h"

ManagerLoginWidget::ManagerLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerLoginWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("管理员认证");
    ui->label_error->clear();
    ui->label_error->setAlignment(Qt::AlignHCenter);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);//设置密码输入框
    connect(ui->pushButton_confirm, &QPushButton::clicked, this, &ManagerLoginWidget::confirm);//连接确认按钮与确认函数
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &ManagerLoginWidget::cancel);//连接取消按钮与取消函数
}

ManagerLoginWidget::~ManagerLoginWidget()
{
    delete ui;
}
void ManagerLoginWidget::confirm()
{
    mlc = new ManagerLoginController(ui->lineEdit_account,ui->lineEdit_password, 123);//生成一个登陆控制器
    login_res = mlc->ManagerLogin();//发送认证请求
    if(std::get<0>(login_res) == true)//认证成功
    {
        emit certified_signal();
        this->close();
    }else//认证失败
    {
        ui->lineEdit_password->clear();//清空密码输入框
        ui->label_error->setText(std::get<1>(login_res));//错误提示信息
    }
}

void ManagerLoginWidget::cancel()
{
    emit cancel_signal();
    this->close();
}
