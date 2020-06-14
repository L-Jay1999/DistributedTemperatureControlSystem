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
//        this->_mode = WorkingMode(1);
        _mode = WorkingMode(1);
        ui->lineEdit_temperature->setText("28");
        //TODO 将初始的所有空调模式更改设置
//        SetModeRequest *setmoderequest = new SetModeRequest(_mode);
//        bool result = setmoderequest->Send();

    }else{
        _mode = WorkingMode(0);
        ui->lineEdit_temperature->setText("22");
    }
    //TODO 控制从控机mode and temperature
    emit confirm_signal();
    this->hide();
}

int ParameterWidget::getTemperature()
{
    return temperature;
}

WorkingMode ParameterWidget::getMode()
{
//     qDebug() << "Mode:" << mode;
    return _mode;
}


