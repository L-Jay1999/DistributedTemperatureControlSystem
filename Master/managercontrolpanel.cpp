﻿#include "managercontrolpanel.h"
#include "ui_managercontrolpanel.h"

ManagerControlPanel::ManagerControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerControlPanel)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("控制面板");
    this->setFixedSize(this->width(),this->height());
    connect(ui->pushButton_logout,&QPushButton::clicked,    this,&ManagerControlPanel::logout);//登出按钮
    connect(ui->pushButton_power,&QPushButton::clicked,     this,&ManagerControlPanel::switch_to_power);//电源控制按钮
    connect(ui->pushButton_parameter,&QPushButton::clicked, this,&ManagerControlPanel::switch_to_parameter);//参数设置按钮
    connect(ui->pushButton_log,&QPushButton::clicked,       this,&ManagerControlPanel::switch_to_log);//运行日志按钮
    connect(ui->pushButton_monitor,&QPushButton::clicked,   this,&ManagerControlPanel::switch_to_monitor);//监控信息按钮
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
    pw->close();
}

void ManagerControlPanel::reshow_power()
{

//    ui->label_mode->setText(pw->getMode());
//    ui->label_power->setText(psw->getPower());
    this->power = psw->getPower();
//    this->mode = pw->getMode();
    qDebug() << "getPower:" << psw->getPower();
//    qDebug() << "getMode:" << pw->getMode();
        ui->label_power->setText(this->power);
    this->show();

}

void ManagerControlPanel::reshow_mode()
{

//    ui->label_mode->setText(pw->getMode());
//    ui->label_power->setText(psw->getPower());
//    this->power = psw->getPower();
    this->mode = pw->getMode();
//    qDebug() << "getPower:" << psw->getPower();
    qDebug() << "getMode:" << pw->getMode();
    ui->label_mode->setText(this->mode);
    this->show();

}


void ManagerControlPanel::switch_to_power()
{
    psw = new PowerSupplyWidget;
    psw->show();
    this->hide();
    connect(psw,SIGNAL(cancel_signal()),this,SLOT(reshow_power()));//连接返回信号与回显
}

void ManagerControlPanel::switch_to_parameter()
{
    pw = new ParameterWidget;
    pw->show();
    this->hide();
    connect(pw,SIGNAL(cancel_signal()), this, SLOT(reshow_mode()));
    connect(pw, SIGNAL(confirm_signal()), this, SLOT(reshow_mode()));
//    ui->label_mode->setText(pw->getMode());
}

void ManagerControlPanel::switch_to_log()
{

}

void ManagerControlPanel::switch_to_monitor()
{
    mw = new MonitorWidget;
    mw->resize(960, 640);
    mw->setWindowTitle(QString::fromUtf8("房间监控状况"));
    mw->show();
}