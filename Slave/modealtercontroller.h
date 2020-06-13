#ifndef MODEALTERCONTROLLER_H
#define MODEALTERCONTROLLER_H

#include <QObject>

#include "common.h"

class ModeAlterController : public QObject
{
    Q_OBJECT
public:
    explicit ModeAlterController(QObject *parent = nullptr);
    void SetMode(const WorkingMode mode);

signals:
    void ModeChanged(WorkingMode mode);

};

#endif // MODEALTERCONTROLLER_H
