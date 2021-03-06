﻿#include "slavecontrolwindow.h"
#include "ui_slavecontrolwindow.h"

SlaveControlWindow::SlaveControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlaveControlWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("从控机"));
    _temperature_lcd = ui->_temperature_lcd;
    _roomtemperature_lcd = ui->_roomtemperature_lcd;
    _cost_lcd = ui->_cost_lcd;
    _windspeed_lcd = ui->_windspeed_lcd;
    _usage_lcd = ui->_usage_lcd;
    _mode_text = ui->_mode_text;
    _wind_text = ui->_wind;
    _textbrowser = ui->textBrowser;

    _wind_text->clear();
    ShutDownDisplays();

    _sensor = new Sensor(this);
    _sensor->setHasPower(false);
    _gettemperaturecontroller = new GetTemperatureController(this, _sensor);

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(GetRoomTemperature()));

    _modealtercontroller = new ModeAlterController(this);

    _windcontrollerfromm = new WindControllerFromM(this);

    qDebug() << "slavecontrolwindow create";
}

SlaveControlWindow::~SlaveControlWindow()
{
    if (_is_open)
        on_shutdownbtn_clicked();
    delete ui;
}

int SlaveControlWindow::WindSpeed(SpeedLevel speedlevel)
{
    int level = (int)speedlevel;
    return level + 1;
}

SpeedLevel SlaveControlWindow::WindSpeed(int speedlevel)
{
    switch (speedlevel) {
    case 1:
        return SpeedLevel::LOW;
        break;
    case 2:
        return SpeedLevel::MID;
        break;
    case 3:
        return SpeedLevel::HIGH;
        break;
    default:
        return SpeedLevel::LOW;
        break;
    }
}

void SlaveControlWindow::ModeDisplay()
{
    if(_mode == WorkingMode::COLD){
        _mode_text->setText("制冷");
    }
    else{
        _mode_text->setText("制热");
    }
}

void SlaveControlWindow::WindDisplay()
{
    if(_is_wind){
        _wind_text->setText("送风中");
    }
    else{
        _wind_text->setText("暂停工作");
    }

}

void SlaveControlWindow::UpdateBound()
{
    if(_mode == WorkingMode::COLD){
        _upperbound = 25.0;
        _lowerbound = 18.0;
        if(_temperature > 25.0){
            _temperature = 25.0;
            _temperature_lcd->display(_temperature);
            _sensor->setTargetDegree(_temperature);
        }
        else if(_temperature < 18.0){
            _temperature = 18.0;
            _temperature_lcd->display(_temperature);
            _sensor->setTargetDegree(_temperature);
        }
    }
    else{
        _upperbound = 30.0;
        _lowerbound = 25.0;
        if(_temperature < 25.0){
            _temperature = 25.0;
            _temperature_lcd->display(_temperature);
            _sensor->setTargetDegree(_temperature);
        }
        else if(_temperature > 30.0){
            _temperature = 30.0;
            _temperature_lcd->display(_temperature);
            _sensor->setTargetDegree(_temperature);
        }
    }
}

void SlaveControlWindow::ShutDownDisplays()
{
    _temperature_lcd->display(88.88);
    _windspeed_lcd->display(8);
    _roomtemperature_lcd->display(88.88);
    _usage_lcd->display(88.88);
    _cost_lcd->display(88.88);
    _wind_text->clear();
//    _textbrowser->clear();
}

void SlaveControlWindow::setUser(User *value)
{
    _user = value;
    _usage = _user->getUsage();
    _cost = _user->getCost();
    _useandcostcontroller = new UseAndCostController(this, _user);
}

void SlaveControlWindow::on_shutdownbtn_clicked()
{
    if (_is_open)
    {
        ShutDownController shut_down(this);
        if (!shut_down.ShutDown( _user->getRoomID()))
        {
            // TODO handle connection fails
            qDebug() << "shut down fail!";
        }
//        _timer->stop();
//        ShutDownDisplays();
//        _is_open = false;
//        _sensor->setIsWind(false);
//        _sensor->setHasPower(false);
        ForceShutDown();
    }
    else
    {
        _textbrowser->clear();
        qDebug() << "login window";
        UserLoginDialog *log_in_dialog = new UserLoginDialog(this);
        if (log_in_dialog->exec() == QDialog::Accepted)
        {
            _windspeed = WindSpeed(SpeedLevel::LOW);

            _sensor->setTargetDegreeWithoutUpdate(_temperature);
            _sensor->setWindSpeed(WindSpeed(_windspeed));
            _sensor->setWorkingMode(_mode);
            _sensor->setHasPower(true);
            GetRoomTemperature();

            _timer->start(1000);

            _temperature_lcd->display(_temperature);
            _windspeed_lcd->display(_windspeed);

            _usage_lcd->display(_usage);
            _cost_lcd->display(_cost);
            _is_open = true;

            ModeDisplay();
            UpdateBound();

            WindDisplay();
            SendWind();
            _sensor->setIsWindWithoutUpdate(true);
        }
    }
}

void SlaveControlWindow::on_windspeedbtn_clicked()
{
    if (!_is_open)
        return;

    if(_windspeed == 3){
        _windspeed = 1;
    }
    else{
        _windspeed += 1;
    }
    SetSpeedController setspeedcontroller(this);
    if(setspeedcontroller.Set(_user->getRoomID(), WindSpeed(_windspeed))){
        _windspeed_lcd->display(_windspeed);
        _sensor->setWindSpeed(WindSpeed(_windspeed));
    }
    else{
        if(_windspeed == 1){
            _windspeed = 3;
        }
        else{
            _windspeed -= 1;
        }
    }
//    _windspeed_lcd->display(_windspeed);
//    _sensor->setWindSpeed(WindSpeed(_windspeed));
}

void SlaveControlWindow::on_uptemperaturebtn_clicked()
{
    if (!_is_open)
        return;

    if(_temperature >= _upperbound){
        TextAppend("温度已达上界");
        return;
    }

    _temperature += 1.0;
    SetTemperatureController settemperaturecontroller(this);
    if(settemperaturecontroller.Set(_user->getRoomID(), _temperature)){
        _temperature_lcd->display(_temperature);
        _sensor->setTargetDegreeWithoutUpdate(_temperature);
        SendWind();
    }
    else{
        _temperature -= 1.0;
    }
//    _temperature_lcd->display(_temperature);
//    _sensor->setTargetDegreeWithoutUpdate(_temperature);
//    SendWind();
}

void SlaveControlWindow::on_downtemperaturebtn_clicked()
{
    if (!_is_open)
        return;

    if(_temperature <= _lowerbound){
        TextAppend("温度已达下界");
        return;
    }

    _temperature -= 1.0;
    SetTemperatureController settemperaturecontroller(this);
    if(settemperaturecontroller.Set(_user->getRoomID(), _temperature)){
        _temperature_lcd->display(_temperature);
        _sensor->setTargetDegreeWithoutUpdate(_temperature);
        SendWind();
    }
    else{
        _temperature += 1.0;
    }
//    _temperature_lcd->display(_temperature);
//    _sensor->setTargetDegreeWithoutUpdate(_temperature);
//    SendWind();
}

void SlaveControlWindow::GetRoomTemperature()
{
    _roomtemperature = _sensor->GetTemperature();
    _roomtemperature_lcd->display(_roomtemperature);
}

void SlaveControlWindow::GetMode(int mode_, double default_degree)
{
    WorkingMode mode = static_cast<WorkingMode>(mode_);
    if(mode == _mode){
        _sensor->setWorkingMode(_mode);
        _sensor->setTargetDegree(default_degree);
        UpdateBound();
        ModeDisplay();
    }
    else{
        _mode = mode;
        _temperature = default_degree;
        _sensor->setWorkingMode(_mode);
        _sensor->setTargetDegree(default_degree);
        UpdateBound();
        ModeDisplay();
        _temperature_lcd->display(_temperature);
    }

    TextAppend("主控机传来模式修改信号");
}

bool SlaveControlWindow::SendWind()
{
    qDebug() << "SendWind Function" << _temperature << _roomtemperature;

    if(_temperature < _roomtemperature && _mode == WorkingMode::HOT){
        TextAppend("加热状态温度小于室温，阻止送风");
        qDebug() << "SendWind Fail!";
        WindController windcontroller(this);
        windcontroller.Send(_user->getRoomID(), false);
        return false;
    }
    else if(_temperature > _roomtemperature && _mode == WorkingMode::COLD){
        TextAppend("制冷状态温度高于室温，阻止送风");
        qDebug() << "SendWind Fail!";
        WindController windcontroller(this);
        windcontroller.Send(_user->getRoomID(), false);
        return false;
    }

    if(std::abs(_temperature - _roomtemperature) >= 1.0){
        WindController windcontroller(this);
        windcontroller.Send(_user->getRoomID(), true);
//        bool result = windcontroller.Send(_user->getRoomID(), true);
//        bool result = true;
//        if(result){
//            _is_wind = true;
//        }
//        _sensor->setIsWind(_is_wind);
//        WindDisplay();
//        return result;
    }
    return true;
//    else{
//        _is_wind = false;
//        _sensor->setIsWind(_is_wind);
//        return false;
//    }
}

void SlaveControlWindow::reachTargetDegree()
{
    // TODO 停止送风请求
    WindController windcontroller(this);
    windcontroller.Send(_user->getRoomID(), false);
//    bool result = windcontroller.Send(_user->getRoomID(), false);
//    bool result = true;
//    if(result){
//        _is_wind = false;
//    }
//    _sensor->setIsWindWithoutUpdate(_is_wind);
//    WindDisplay();
}

void SlaveControlWindow::higherThanTargetDegreePlusOne()
{
    if (_is_open)
    {
	WindController windcontroller(this);
    windcontroller.Send(_user->getRoomID(), true);
//	bool result = windcontroller.Send(_user->getRoomID(), true);
//        bool result = true;
//        if (result)
//        {
//            _sensor->setIsWindWithoutUpdate(true);
//            _is_wind = true;
//            WindDisplay();
//        }
//        else
//        {
//            // TODO handle false condition
//            qDebug() << "higherThanTargetDegreePlusOne error!";
//        }
    }
}

void SlaveControlWindow::SetLoginUser(const QString &room_id, const QString &user_id, WorkingMode mode, double init_temp)
{
    setUser(new User(room_id, user_id));
    _mode = mode;
    _temperature = init_temp;
}

void SlaveControlWindow::WindControlFromM(bool is_in_queue)
{
    _is_wind = is_in_queue;
    _sensor->setIsWindWithoutUpdate(_is_wind);
    WindDisplay();
    if(is_in_queue)
        TextAppend("主控机传来送风信号True");
    else
        TextAppend("主控机传来送风信号False");
}

void SlaveControlWindow::TextAppend(QString s)
{
    _textbrowser->append(s);
}

void SlaveControlWindow::ForceShutDown()
{
    _timer->stop();
    ShutDownDisplays();
    _is_open = false;
    _sensor->setIsWind(false);
    _sensor->setHasPower(false);
}

void SlaveControlWindow::GetUseandCost()
{
    if (!_is_open)
    {
        _user->setUsage(0.0);
        _user->setCost(0.0);
    }
    else
    {
        _usage = _user->getUsage();
        _cost = _user->getCost();
        _usage_lcd->display(_usage);
        _cost_lcd->display(_cost);
        TextAppend("主控机传来use和cost");
    }
}
