#include "parameterwidget.h"
#include "ui_parameterwidget.h"

ParameterWidget::ParameterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("参数设置");
    this->setFixedSize(this->width(),this->height());
    connect(ui->pushButton_cancel,&QPushButton::clicked,this,&ParameterWidget::cancel);
    connect(ui->pushButton_confirm,&QPushButton::clicked,this,&ParameterWidget::confirm);
}

ParameterWidget::~ParameterWidget()
{
    delete ui;
}

void ParameterWidget::cancel()
{
    emit cancel_signal();
    this->hide();
}

void ParameterWidget::confirm()
{
    this->temperature = ui->lineEdit_temperature->text().toInt();
    if(ui->radioButton_hot->isChecked())
    {
        this->mode = "hot";
    }else{
        this->mode = "cold";
    }
    getMode();
    qDebug() << "Mode:" << mode;
    emit confirm_signal();
    this->hide();
}

int ParameterWidget::getTemperature()
{
    return temperature;
}

QString ParameterWidget::getMode()
{
//     qDebug() << "Mode:" << mode;
    return mode;
}


