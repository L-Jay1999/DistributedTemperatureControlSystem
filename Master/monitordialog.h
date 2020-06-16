#ifndef MONITORDIALOG_H
#define MONITORDIALOG_H

#include <QDialog>

#include "global.h"
#include "dbaccess.h"

namespace Ui {
class MonitorDialog;
}

class MonitorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MonitorDialog(int interval_sec, QWidget *parent = nullptr);
    ~MonitorDialog();
    void setUpdateInterval(int interval_sec);
private:
    Ui::MonitorDialog *ui;
    Rooms &_rooms;
    // DBAccess _db;
    QTimer _timer;
    int _interval;
private slots:
    void updateTable();
};

#endif // MONITORDIALOG_H
