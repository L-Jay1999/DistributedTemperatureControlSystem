#include "windcontrollerfromm.h"

WindControllerFromM::WindControllerFromM(QObject *parent) : QObject(parent)
{
//    Config::setSlaveControllerPointer(Config::SlaveControllerType::WIND_SCHEDULE, this);
    connect(this, SIGNAL(WindControl(bool)), parent, SLOT(WindControlFromM(bool)));
}

void WindControllerFromM::Set(bool is_in_queue)
{
    emit WindControl(is_in_queue);
}
