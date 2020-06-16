#ifndef MONITOR_DIALOG_H
#define MONITOR_DIALOG_H

#include <QDialog>

namespace Ui {
class MonitorDialog;
}

class MonitorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MonitorDialog(QWidget *parent = nullptr);
    ~MonitorDialog();

private:
    Ui::MonitorDialog *ui;
};

#endif // MONITOR_DIALOG_H
