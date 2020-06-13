#ifndef WINDCONTROLLERFROMM_H
#define WINDCONTROLLERFROMM_H

#include <QObject>

#include "common.h"

class WindControllerFromM : public QObject
{
    Q_OBJECT
public:
    explicit WindControllerFromM(QObject *parent = nullptr);
    void Set(bool is_in_queue);

signals:
    void WindControl(bool is_in_queue);
};

#endif // WINDCONTROLLERFROMM_H
