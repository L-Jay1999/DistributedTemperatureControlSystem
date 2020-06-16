#include "modealtercontroller.h"

ModeAlterController::ModeAlterController(QObject *parent) : QObject(parent)
{
    Config::setSlaveControllerPointer(Config::SlaveControllerType::MODE_ALTER, this);
    connect(this, SIGNAL(ModeChanged(int, double)), parent, SLOT(GetMode(int,double)));
}

void ModeAlterController::SetMode(const WorkingMode mode, const double default_degree)
{
    qDebug() << "CHANGE MODE";
    emit ModeChanged(EnumToInt(mode), default_degree);
}

