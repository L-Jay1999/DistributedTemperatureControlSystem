#include "modealtercontroller.h"

ModeAlterController::ModeAlterController(QObject *parent) : QObject(parent)
{
    Config::setSlaveControllerPointer(Config::SlaveControllerType::MODE_ALTER, this);
    connect(this, SIGNAL(ModeChanged(WorkingMode)), parent, SLOT(GetMode(WorkingMode)));
}

void ModeAlterController::SetMode(const WorkingMode mode)
{
    emit ModeChanged(mode);
}

