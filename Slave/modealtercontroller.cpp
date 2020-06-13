#include "modealtercontroller.h"

ModeAlterController::ModeAlterController(QObject *parent) : QObject(parent)
{

}

void ModeAlterController::SetMode(const WorkingMode mode)
{
    emit ModeChanged(mode);
}

