#include "slavecontrolwindow.h"
#include "ui_slavecontrolwindow.h"

SlaveControlWindow::SlaveControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlaveControlWindow)
{
    ui->setupUi(this);
    _temperature_lcd = ui->_temperature_lcd;
    _roomtemperature_lcd = ui->_roomtemperature_lcd;
    _cost_lcd = ui->_cost_lcd;
    _windspeed_lcd = ui->_windspeed_lcd;
    _usage_lcd = ui->_usage_lcd;
    _mode_text = ui->_mode_text;
    _wind_text = ui->_wind;

    _wind_text->clear();
    ShutDownDisplays();
//    _temperature_lcd->display(_temperature);

//    _windspeed = 1;
//    _windspeed_lcd->display(_windspeed);

    _sensor = new Sensor(this);
//    _sensor->setTargetDegree(_temperature);
//    _sensor->setWindSpeed(WindSpeed(_windspeed));
//    _sensor->setWorkingMode(_mode);
//    GetRoomTemperature();

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(GetRoomTemperature()));
//    _timer->start(5000);

//    _usage = _user->getUsage();
//    _cost = _user->getCost();
//    _usage_lcd->display(_usage);
//    _cost_lcd->display(_cost);
//    _useandcostcontroller = new UseAndCostController(this, _user);
//    Config::setSlaveControllerPointer(Config::SlaveControllerType::USE_COST, _useandcostcontroller);
//    connect(_useandcostcontroller, SIGNAL(UseandCostChanged()), this, SLOT(GetUseandCost()));

//    ModeDisplay();
//    UpdateBound();
    _modealtercontroller = new ModeAlterController(this);
    connect(_modealtercontroller, SIGNAL(ModeChanged(WorkingMode)), this, SLOT(GetMode(WorkingMode)));

//    WindDisplay();
//    SendWind();

    qDebug() << "slavecontrolwindow create";
}

SlaveControlWindow::~SlaveControlWindow()
{
    delete ui;
    exit(0);
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
    }
    else{
        _upperbound = 30.0;
        _lowerbound = 25.0;
        if(_temperature < 25.0){
            _temperature = 25.0;
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
}

void SlaveControlWindow::setUser(User *value)
{
    _user = value;
    _usage = _user->getUsage();
    _cost = _user->getCost();
    _useandcostcontroller = new UseAndCostController(this, _user);
//    Config::setSlaveControllerPointer(Config::SlaveControllerType::USE_COST, _useandcostcontroller);
    connect(_useandcostcontroller, SIGNAL(UseandCostChanged()), this, SLOT(GetUseandCost()));
}

void SlaveControlWindow::on_shutdownbtn_clicked()
{
//    ShutDownController shutdown_controller(_user->getRoomID());
//    if(shutdown_controller.ShutDown()){
//        StartUpWindow *start_up_window = new StartUpWindow();
//        start_up_window->show();
//        Config::clearSlaveListenerPort();
//        // 设定 sensor 不再送风
//        close();
//        qDebug() << "ShutDown";
//    }
//    else{
//        // todo 弹窗表示无法连接到中央空调
//        qDebug() << "ShutDown Fail!";
//    }

//     StartUpWindow *start_up_window = new StartUpWindow();
//     start_up_window->show();
//     Config::clearSlaveListenerPort();
//     close();
    if (_is_open)
    {
//        ShutDownController shut_down(_user->getRoomID());
//        if (!shut_down.ShutDown())
//        {
//            // TODO handle connection fails
//        }
        _timer->stop();
        ShutDownDisplays();
        _wind_text->clear();
        _is_open = false;
        _sensor->setIsWind(false);
    }
    else
    {
        UserLoginDialog *log_in_dialog = new UserLoginDialog(this);
        if (log_in_dialog->exec() == QDialog::Accepted)
        {
            _windspeed = WindSpeed(SpeedLevel::LOW);

            _sensor->setTargetDegreeWithoutUpdate(_temperature);
            _sensor->setWindSpeed(WindSpeed(_windspeed));
            _sensor->setWorkingMode(_mode);
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
//    SetSpeedController setspeedcontroller(_user->getRoomID(), WindSpeed(_windspeed));
//    if(setspeedcontroller.Set()){
//        _windspeed_lcd->display(_windspeed);
//    }
//    else{
//        if(_windspeed == 1){
//            _windspeed = 3;
//        }
//        else{
//            _windspeed -= 1;
//        }
//    }
    _windspeed_lcd->display(_windspeed);
    _sensor->setWindSpeed(WindSpeed(_windspeed));
}

void SlaveControlWindow::on_uptemperaturebtn_clicked()
{
    if (!_is_open)
        return;

    if(_temperature >= _upperbound)
        return;
    _temperature += 1.0;
//    SetTemperatureController settemperaturecontroller(_user->getRoomID(), _temperature);
//    if(settemperaturecontroller.Set()){
//        _temperature_lcd->display(_temperature);
//    }
//    else{
//        _temperature -= 1.0;
//    }
    _temperature_lcd->display(_temperature);
    _sensor->setTargetDegreeWithoutUpdate(_temperature);
    SendWind();
}

void SlaveControlWindow::on_downtemperaturebtn_clicked()
{
    if (!_is_open)
        return;

    if(_temperature <= _lowerbound)
        return;
    _temperature -= 1.0;
//    SetTemperatureController settemperaturecontroller(_user->getRoomID(), _temperature);
//    if(settemperaturecontroller.Set()){
//        _temperature_lcd->display(_temperature);
//    }
//    else{
//        _temperature += 1.0;
//    }
    _temperature_lcd->display(_temperature);
    _sensor->setTargetDegreeWithoutUpdate(_temperature);
    SendWind();
}

void SlaveControlWindow::GetRoomTemperature()
{
    _roomtemperature = _sensor->GetTemperature();
    _roomtemperature_lcd->display(_roomtemperature);
}

void SlaveControlWindow::GetMode(WorkingMode mode)
{
    if(mode == _mode){
        ModeDisplay();
    }
    else{
        if(mode == WorkingMode::HOT){
            if(_temperature <= _roomtemperature)
                return;
            else{
                _mode = mode;
                _sensor->setWorkingMode(_mode);
                UpdateBound();
                ModeDisplay();
            }
        }
        else{
            if(_temperature >= _roomtemperature)
                return;
            else{
                _mode = mode;
                _sensor->setWorkingMode(_mode);
                UpdateBound();
                ModeDisplay();
            }
        }
    }
}

bool SlaveControlWindow::SendWind()
{
    qDebug() << "SendWind" << _temperature << _roomtemperature;
    if(std::abs(_temperature - _roomtemperature) >= 1.0){
//        WindController windcontroller(true, _user->getRoomID());
//        bool result = windcontroller.Send();
        bool result = true;
        if(result){
            _is_wind = true;
        }
        _sensor->setIsWind(_is_wind);
        WindDisplay();
        return result;
    }
    else{
        _is_wind = false;
        _sensor->setIsWind(_is_wind);
        return false;
    }
}

void SlaveControlWindow::reachTargetDegree()
{
    // TODO 停止送风请求
//    WindController windcontroller(false, _user->getRoomID());
//    bool result = windcontroller.Send();
    bool result = true;
    if(result){
        _is_wind = false;
    }
    _sensor->setIsWindWithoutUpdate(_is_wind);
    WindDisplay();
}

void SlaveControlWindow::higherThanTargetDegreePlusOne()
{
    if (_is_open)
    {
        // WindController windcontroller(true, _user->getRoomID());
        // bool result = windcontroller.Send();
        bool result = true;
        if (result)
        {
            _sensor->setIsWindWithoutUpdate(true);
            _is_wind = true;
            WindDisplay();
        }
        else
        {
            // TODO handle false condition
        }
    }
}

void SlaveControlWindow::SetLoginUser(const QString &room_id, const QString &user_id, WorkingMode mode, double init_temp)
{
    setUser(new User(room_id, user_id));
    _mode = mode;
    _temperature = init_temp;
}

void SlaveControlWindow::GetUseandCost()
{
    _usage = _user->getUsage();
    _cost = _user->getCost();
    _usage_lcd->display(_usage);
    _cost_lcd->display(_cost);
}
