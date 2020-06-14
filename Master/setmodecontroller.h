#ifndef SETMODECONTROLLER_H
#define SETMODECONTROLLER_H

#include <QObject>
#include <tuple>
#include <QDebug>

#include "requests.h"
#include "common.h"

class SetModeController : public QObject
{
    Q_OBJECT
public:
    explicit SetModeController(QObject *parent = nullptr);
    bool Set(WorkingMode mode);

signals:

};

#endif // SETMODECONTROLLER_H
