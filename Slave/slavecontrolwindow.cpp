#include "slavecontrolwindow.h"
#include "ui_slavecontrolwindow.h"
#include "startupwindow.h"

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

    _temperature = 25.0;
    _temperature_lcd->display(_temperature);

    _windspeed = 1;
    _windspeed_lcd->display(_windspeed);

    _sensor = new Sensor(this);
    connect(_sensor, SIGNAL(TemperatureChanged()), this, SLOT(GetRoomTemperature()));
//    _roomtemperature = _sensor->GetTemperature(_temperature);
//    _roomtemperature_lcd->display(_roomtemperature);

//    _timer = new QTimer(this);
//    connect(_timer, SIGNAL(timeout()), this, SLOT(GetRoomTemperature()));
//    _timer->start(5000);

    _modealtercontroller = new ModeAlterController(this);
    connect(_modealtercontroller, SIGNAL(ModeChanged(WorkingMode)), this, SLOT(GetMode(WorkingMode)));

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
        _wind_text->setText("暂停");
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

//void SlaveControlWindow::SetInterval()
//{
//    _timer->setInterval(_interval[_windspeed-1]);
//}

void SlaveControlWindow::setUser(User *value)
{
    _user = value;
    _usage = _user->getUsage();
    _cost = _user->getCost();
    _usage_lcd->display(_usage);
    _cost_lcd->display(_cost);
    _useandcostcontroller = new UseAndCostController(this);
    _useandcostcontroller->setUser(_user);
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

     StartUpWindow *start_up_window = new StartUpWindow();
     start_up_window->show();
     Config::clearSlaveListenerPort();
     close();
}

void SlaveControlWindow::on_windspeedbtn_clicked()
{
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
    _sensor->setWindSpeed(_windspeed);
}

void SlaveControlWindow::on_uptemperaturebtn_clicked()
{
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
    _sensor->setTargetDegree(_temperature);
}

void SlaveControlWindow::on_downtemperaturebtn_clicked()
{
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
    _sensor->setTargetDegree(_temperature);
}

void SlaveControlWindow::GetRoomTemperature()
{
    _roomtemperature = _sensor->GetTemperature();
    _roomtemperature_lcd->display(_roomtemperature);
}

void SlaveControlWindow::GetMode(WorkingMode mode)
{
    if(mode == _mode){
        return;
    }
    else{
        if(mode == WorkingMode::HOT){
            if(_temperature <= _roomtemperature)
                return;
            else{
                _mode = mode;
                UpdateBound();
                ModeDisplay();
            }
        }
        else{
            if(_temperature >= _roomtemperature)
                return;
            else{
                _mode = mode;
                UpdateBound();
                ModeDisplay();
            }
        }
    }
}

void SlaveControlWindow::GetUseandCost()
{
    _usage = _user->getUsage();
    _cost = _user->getCost();
    _usage_lcd->display(_usage);
    _cost_lcd->display(_cost);
}
