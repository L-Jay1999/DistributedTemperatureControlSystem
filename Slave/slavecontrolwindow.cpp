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

    _temperature = 25.0;
    _temperature_lcd->display(_temperature);

    _windspeed = 1;
    _windspeed_lcd->display(_windspeed);

    _sensor = new Sensor(25.0);
    _roomtemperature = _sensor->GetTemperature(_temperature);
    _roomtemperature_lcd->display(_roomtemperature);

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(GetRoomTemperature()));
    _timer->start(5000);

    _useandcostcontroller = new UseAndCostController(this);
    _useandcostcontroller->setUser(_user);
//    Config::setSlaveControllerPointer(Config::SlaveControllerType::USE_COST, _useandcostcontroller);
//    connect(_useandcostcontroller, SIGNAL(UseandCostChanged()), this, SLOT(GetUseandCost()));
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

void SlaveControlWindow::setUser(User *value)
{
    _user = value;
    _usage = _user->getUsage();
    _cost = _user->getCost();
    _usage_lcd->display(_usage);
    _cost_lcd->display(_cost);
}

void SlaveControlWindow::on_shutdownbtn_clicked()
{
//    ShutDownController *shutdowncontroller = new ShutDownController(_user->getRoomID());
//    if(shutdowncontroller->ShutDown()){
//        // todo
//        qDebug() << "ShutDown"
//    }
//    else{
//        // todo
//        qDebug() << "ShutDown Fail!"
//    }
//    delete shutdowncontroller;
    exit(0);
}

void SlaveControlWindow::on_windspeedbtn_clicked()
{
    if(_windspeed == 3){
        _windspeed = 1;
    }
    else{
        _windspeed += 1;
    }
//    SetSpeedController *setspeedcontroller = new SetSpeedController(_user->getRoomID(), WindSpeed(_windspeed));
//    if(setspeedcontroller->Set()){
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
//    delete setspeedcontroller;
    _windspeed_lcd->display(_windspeed);
}

void SlaveControlWindow::on_uptemperaturebtn_clicked()
{
    if(_temperature >= 40.0)
        return;
    _temperature += 0.5;
//    SetTemperatureController *settemperaturecontroller = new SetTemperatureController(_user->getRoomID(), _temperature);
//    if(settemperaturecontroller->Set()){
//        _temperature_lcd->display(_temperature);
//    }
//    else{
//        _temperature -= 0.5;
//    }
//    delete settemperaturecontroller;
    _temperature_lcd->display(_temperature);
}

void SlaveControlWindow::on_downtemperaturebtn_clicked()
{
    if(_temperature <= 20.0)
        return;
    _temperature -= 0.5;
//    SetTemperatureController *settemperaturecontroller = new SetTemperatureController(_user->getRoomID(), _temperature);
//    if(settemperaturecontroller->Set()){
//        _temperature_lcd->display(_temperature);
//    }
//    else{
//        _temperature += 0.5;
//    }
//    delete settemperaturecontroller;
    _temperature_lcd->display(_temperature);
}

void SlaveControlWindow::GetRoomTemperature()
{
    _roomtemperature = _sensor->GetTemperature(_temperature);
    _roomtemperature_lcd->display(_roomtemperature);
}

void SlaveControlWindow::GetUseandCost()
{
    _usage = _user->getUsage();
    _cost = _user->getCost();
    _usage_lcd->display(_usage);
    _cost_lcd->display(_cost);
}
