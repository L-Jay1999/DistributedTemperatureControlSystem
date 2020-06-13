#include "managercontrolpanel.h"
#include "ui_managercontrolpanel.h"

ManagerControlPanel::ManagerControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerControlPanel)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("控制面板");
    this->setFixedSize(this->width(),this->height());
    connect(ui->pushButton_logout,&QPushButton::clicked,    this,&ManagerControlPanel::logout);             //管理员登出
    connect(ui->pushButton_power,&QPushButton::clicked,     this,&ManagerControlPanel::switch_to_power);    //电源控制
    connect(ui->pushButton_parameter,&QPushButton::clicked, this,&ManagerControlPanel::switch_to_parameter);//参数设置
    connect(ui->pushButton_log,&QPushButton::clicked,       this,&ManagerControlPanel::switch_to_log);      //运行日志
    connect(ui->pushButton_monitor,&QPushButton::clicked,   this,&ManagerControlPanel::switch_to_monitor);  //监控信息
    connect(ui->pushButton_user,&QPushButton::clicked,      this,&ManagerControlPanel::switch_to_user);     //用户管理
    psw = new PowerSupplyWidget;
    umw = new UserManagementWidget;
}

ManagerControlPanel::~ManagerControlPanel()
{
    delete ui;
}

void ManagerControlPanel::logout()
{
    emit logout_signal();
    this->close();
    psw->close();
    umw->close();
}

void ManagerControlPanel::reshow()
{
    this->show();
}

void ManagerControlPanel::switch_to_power()
{
    psw->show();
    this->hide();
    connect(psw,SIGNAL(cancel_signal()),this,SLOT(reshow()));//连接返回信号与回显
}

void ManagerControlPanel::switch_to_parameter()
{

}

void ManagerControlPanel::switch_to_log()
{

}

void ManagerControlPanel::switch_to_monitor()
{

}

void ManagerControlPanel::switch_to_user()
{
    umw->show();
    this->hide();
    connect(umw,SIGNAL(cancel_signal()),this,SLOT(reshow()));//连接返回信号与回显
}
