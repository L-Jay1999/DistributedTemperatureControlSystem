#include "modealtercontroller.h"

ModeAlterController::ModeAlterController(QObject *parent) : QObject(parent)
{
    Config::setSlaveControllerPointer(Config::SlaveControllerType::MODE_ALTER, this);
    connect(this, SIGNAL(ModeChanged(WorkingMode, double)), parent, SLOT(GetMode(WorkingMode,double)));
}

void ModeAlterController::SetMode(const WorkingMode mode, const double default_degree)
{
    emit ModeChanged(mode, default_degree);
}

