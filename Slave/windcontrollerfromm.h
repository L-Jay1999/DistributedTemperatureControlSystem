#ifndef WINDCONTROLLERFROMM_H
#define WINDCONTROLLERFROMM_H

#include <QObject>

#include "common.h"

class WindControllerFromM : public QObject
{
    Q_OBJECT
public:

    explicit WindControllerFromM(QObject *parent) : QObject(parent)
    {
    //    Config::setSlaveControllerPointer(Config::SlaveControllerType::WIND_SCHEDULE, this);
        connect(this, SIGNAL(WindControl(bool)), parent, SLOT(WindControlFromM(bool)));
    }

    void Set(bool is_in_queue)
    {
        emit WindControl(is_in_queue);
    }

signals:
    void WindControl(bool is_in_queue);
};

#endif // WINDCONTROLLERFROMM_H
