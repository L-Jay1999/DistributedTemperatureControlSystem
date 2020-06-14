#include "managercontrolpanel.h"
#include "ui_managercontrolpanel.h"

#include <QString>
#include <QMessageBox>

#include <chrono>

#include "../CommonLib/requests.h"
#include "global.h"

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
    connect(ui->pushButton_mode,&QPushButton::clicked,      this,&ManagerControlPanel::change_mode);//参数设置
    connect(ui->pushButton_rate_up, &QPushButton::clicked,  this,&ManagerControlPanel::rate_up);
    connect(ui->pushButton_rate_down, &QPushButton::clicked,this,&ManagerControlPanel::rate_down);
    connect(ui->pushButton_detail,&QPushButton::clicked,    this,&ManagerControlPanel::switch_to_detail);   //查看详单
    connect(ui->pushButton_report,&QPushButton::clicked,    this,&ManagerControlPanel::switch_to_report);   //查看报表
    connect(ui->pushButton_monitor,&QPushButton::clicked,   this,&ManagerControlPanel::switch_to_monitor);  //监控信息
    connect(ui->pushButton_user,&QPushButton::clicked,      this,&ManagerControlPanel::switch_to_user);     //用户管理
    connect(this, &ManagerControlPanel::SetErrorInfoTextSignal,   this,&ManagerControlPanel::set_error_info_text);
    connect(&clear_error_info_timer, &QTimer::timeout, this, &ManagerControlPanel::clear_error_info_text);
    psw = new PowerSupplyWidget;
    umw = new UserManagementWidget;
    mw = new MonitorWidget;
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
    if (!_has_power)
        ui->label_mode->setText("无");
    else
        setModeLabelText();
}

void ManagerControlPanel::switch_to_detail()
{

}

void ManagerControlPanel::switch_to_report()
{

}

void ManagerControlPanel::switch_to_monitor()
{
    mw->show();
    this->hide();
    connect(mw,SIGNAL(cancel_signal()),this,SLOT(reshow()));//连接返回信号与回显
}

void ManagerControlPanel::switch_to_user()
{
    umw->show();
    this->hide();
    connect(umw,SIGNAL(cancel_signal()),this,SLOT(reshow()));//连接返回信号与回显
}

void ManagerControlPanel::set_power_label_text(bool has_power)
{
    ui->label_power->setText(has_power ? "开启" : "关闭");
}

void ManagerControlPanel::change_mode()
{
    using namespace std::chrono_literals;
    if (!_has_power)
    {
        emit SetErrorInfoTextSignal("空调处于关机状态，请开机后重试");
        return;
    }

    auto room_ids = getRooms().getRoomIDs();
    if (_mode == WorkingMode::HOT)
        _mode = WorkingMode::COLD;
    else
        _mode = WorkingMode::HOT;

    for (const auto &room_id : room_ids)
    {
        SetModeRequest mode_request(_mode, room_id);
        auto [err, is_suc] = mode_request.Send();
        if (err.hasError())
        {
            emit SetErrorInfoTextSignal(err.err_str + "2 秒后重传");
            std::this_thread::sleep_for(3s);
            auto [err_tmp, is_suc_tmp] = mode_request.Send();
            if (err_tmp.hasError())
            {
                emit SetErrorInfoTextSignal(QString("与房间%1连接失败，与从控机的连接已断开").arg(room_id));
                getRooms().delRoomIfExists(room_id);
                // TODO 停止送风，修改 UseAndCost 以及 Schedule
            }
        }
    }
    emit SetErrorInfoTextSignal("成功修改工作模式");
    setModeLabelText();
}

void ManagerControlPanel::set_error_info_text(const QString &err_info)
{
    clear_error_info_timer.stop();
    ui->label_error_info->setText(err_info);
    clear_error_info_timer.start(5000);
}

void ManagerControlPanel::clear_error_info_text()
{
    ui->label_error_info->clear();
}

void ManagerControlPanel::ChangeRate(bool is_rate_up)
{
    if (is_rate_up && _rate < 10)
    {
        _rate++;
        // TODO 通知监控改变刷新间隔
    }
    else if (!is_rate_up && _rate > 3)
    {
        _rate--;
        // TODO 通知监控改变刷新间隔
    }
    else
    {
        emit SetErrorInfoTextSignal("频率已达上限或下限");
    }
    setRateLabelText();
}

void ManagerControlPanel::rate_up()
{
    ChangeRate(true);
}

void ManagerControlPanel::rate_down()
{
    ChangeRate(false);
}
