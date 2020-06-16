#ifndef MODEALTERCONTROLLER_H
#define MODEALTERCONTROLLER_H

#include <QObject>

#include "common.h"

class ModeAlterController : public QObject
{
    Q_OBJECT
public:
    explicit ModeAlterController(QObject *parent = nullptr);
    void SetMode(const WorkingMode mode, const double default_degree);

signals:
    void ModeChanged(int mode, double default_degree);

};

#endif // MODEALTERCONTROLLER_H
