#include "managercontrolpanel.h"
#include "ui_managercontrolpanel.h"

ManagerControlPanel::ManagerControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerControlPanel)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("控制面板");
    connect(ui->pushButton_logout,&QPushButton::clicked,this,&ManagerControlPanel::logout);//连接登出按钮与登出函数
}

ManagerControlPanel::~ManagerControlPanel()
{
    delete ui;
}
void ManagerControlPanel::logout()
{
    emit logout_signal();
    this->close();
}
