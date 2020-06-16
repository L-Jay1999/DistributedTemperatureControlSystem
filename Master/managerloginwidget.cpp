#include "managerloginwidget.h"
#include "ui_managerloginwidget.h"

ManagerLoginWidget::ManagerLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerLoginWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle(QStringLiteral("管理员认证"));
    this->setFixedSize(this->width(),this->height());
    ui->label_error->clear();
    ui->label_error->setAlignment(Qt::AlignHCenter);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);//设置密码输入框
    connect(ui->pushButton_confirm, &QPushButton::clicked, this, &ManagerLoginWidget::confirm);//连接确认按钮与确认函数
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &ManagerLoginWidget::cancel);//连接取消按钮与取消函数
    ui->pushButton_confirm->setShortcut(Qt::Key_Enter);//绑定字母区回车键
}

ManagerLoginWidget::~ManagerLoginWidget()
{
    delete ui;
}
std::tuple<bool,QString> ManagerLoginWidget::Login()
{
    auto mlc = ManagerLoginController(ui->lineEdit_account->text(),ui->lineEdit_password->text());//生成一个登陆控制器
    return mlc.ManagerLogin();//发送认证请求
}

void ManagerLoginWidget::confirm()
{
    auto [login_res, err_info] = Login();
    if(login_res)//认证成功
    {
        emit certified_signal(ui->lineEdit_account->text());
        this->close();
    }
    else//认证失败
    {
        ui->lineEdit_password->clear();//清空密码输入框
        ui->label_error->setText(err_info);//错误提示信息
    }
}

void ManagerLoginWidget::cancel()
{
    emit cancel_signal();
    this->close();
}
