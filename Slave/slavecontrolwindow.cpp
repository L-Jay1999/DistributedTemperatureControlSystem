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

    _temperature_lcd->display(36.2);
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
}

void SlaveControlWindow::on_shutdownbtn_clicked()
{
    ShutDownController *shutdowncontroller = new ShutDownController(_user->getRoomID());
    if(shutdowncontroller->ShutDown()){
        // todo
    }
    else{
        // todo
    }
    delete shutdowncontroller;
}

void SlaveControlWindow::on_windspeedbtn_clicked()
{
    if(_windspeed == 3){
        _windspeed = 1;
    }
    else{
        _windspeed += 1;
    }
    SetSpeedController *setspeedcontroller = new SetSpeedController(_user->getRoomID(), WindSpeed(_windspeed));
    if(setspeedcontroller->Set()){
        _windspeed_lcd->display(_windspeed);
    }
    else{
        if(_windspeed == 1){
            _windspeed = 3;
        }
        else{
            _windspeed -= 1;
        }
    }
    delete setspeedcontroller;
}

void SlaveControlWindow::on_uptemperaturebtn_clicked()
{
    if(_temperature >= 40.0)
        return;
    _temperature += 0.5;
    SetTemperatureController *settemperaturecontroller = new SetTemperatureController(_user->getRoomID(), _temperature);
    if(settemperaturecontroller->Set()){
        _temperature_lcd->display(_temperature);
    }
    else{
        _temperature -= 0.5;
    }
    delete settemperaturecontroller;
}

void SlaveControlWindow::on_downtemperaturebtn_clicked()
{
    if(_temperature <= 20.0)
        return;
    _temperature -= 0.5;
    SetTemperatureController *settemperaturecontroller = new SetTemperatureController(_user->getRoomID(), _temperature);
    if(settemperaturecontroller->Set()){
        _temperature_lcd->display(_temperature);
    }
    else{
        _temperature += 0.5;
    }
    delete settemperaturecontroller;
}
