﻿#include "powersupplywidget.h"
#include "ui_powersupplywidget.h"
PowerSupplyWidget::PowerSupplyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerSupplyWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("电源控制");
    this->setFixedSize(this->width(),this->height());
    connect(ui->pushButton_cancel,&QPushButton::clicked,this,&PowerSupplyWidget::cancel);
    connect(ui->pushButton_on,&QPushButton::clicked,this,&PowerSupplyWidget::clicked_on);
    connect(ui->pushButton_off,&QPushButton::clicked,this,&PowerSupplyWidget::clicked_off);
}

PowerSupplyWidget::~PowerSupplyWidget()
{
    delete ui;
}

void PowerSupplyWidget::cancel()
{
    emit cancel_signal();
    this->hide();
}

void PowerSupplyWidget::clicked_on()
{
    QString text = QStringLiteral("启动中央空调");
    ocd = new OperationConfirmationDialog;
    ocd->setText(text);
    int res = ocd->exec();
    if(res == QDialog::Accepted)
    {
        StartSystem();
    }
}

void PowerSupplyWidget::clicked_off()
{
    QString text = QStringLiteral("关闭中央空调");
    ocd = new OperationConfirmationDialog;
    ocd->setText(text);
    int res = ocd->exec();
    if(res == QDialog::Accepted)
    {
        ShutDownSystem();
    }
}

void PowerSupplyWidget::StartSystem()
{
    ui->label_power->setText(QStringLiteral("开启"));
}

void PowerSupplyWidget::ShutDownSystem()
{
    ui->label_power->setText(QStringLiteral("关闭"));
}