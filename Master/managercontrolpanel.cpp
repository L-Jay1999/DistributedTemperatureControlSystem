#include "managercontrolpanel.h"
#include "ui_managercontrolpanel.h"

#include <QString>
#include <QMessageBox>

ManagerControlPanel::ManagerControlPanel(const QString &manager_account, QWidget *parent) :
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
    connect(ui->pushButton_detail,&QPushButton::clicked,    this,&ManagerControlPanel::switch_to_detail);   //查看详单
    connect(ui->pushButton_report,&QPushButton::clicked,    this,&ManagerControlPanel::switch_to_report);   //查看报表
    connect(ui->pushButton_monitor,&QPushButton::clicked,   this,&ManagerControlPanel::switch_to_monitor);  //监控信息
    connect(ui->pushButton_user,&QPushButton::clicked,      this,&ManagerControlPanel::switch_to_user);     //用户管理
    psw = new PowerSupplyWidget;
    umw = new UserManagementWidget;
    setModeLabelText();
    setPowerLabelText();
    ui->label_manager->setText(manager_account);
    setRateLabelText();
}

ManagerControlPanel::~ManagerControlPanel()
{
    delete ui;
}

void ManagerControlPanel::setPowerLabelText()
{
    ui->label_power->setText(_has_power ? "开机" : "关机");
}

void ManagerControlPanel::setModeLabelText()
{
    if (_mode == WorkingMode::COLD)
        ui->label_mode->setText("制冷");
    else
        ui->label_mode->setText("制热");
}

void ManagerControlPanel::setRateLabelText()
{
    ui->label_rate->setText(QString::number(_rate) + "秒");
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
    QString msg = "确定要将电源状态改变为%1状态吗？";
    if (_has_power)
        msg = msg.arg("关闭");
    else
        msg = msg.arg("开启");
    if(QMessageBox::Yes == QMessageBox::warning(this, "改变电源状态", msg, QMessageBox::Yes | QMessageBox::No))
    {
        _has_power = !_has_power;
        setPowerLabelText();
    }
}

void ManagerControlPanel::switch_to_parameter()
{
    pw->show();
    this->hide();
    connect(pw,SIGNAL(cancel_signal()),this,SLOT(reshow()));
}

void ManagerControlPanel::switch_to_detail()
{

}

void ManagerControlPanel::switch_to_report()
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

void ManagerControlPanel::set_power(bool has_power)
{
    ui->label_power->setText(has_power ? "开启" : "关闭");
}
