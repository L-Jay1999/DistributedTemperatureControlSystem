#ifndef POWERSUPPLYWIDGET_H
#define POWERSUPPLYWIDGET_H

#include <QWidget>
#include "operationconfirmationdialog.h"

namespace Ui {
class PowerSupplyWidget;
}

class PowerSupplyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerSupplyWidget(QWidget *parent = 0);
    ~PowerSupplyWidget();
public:
    QString getText();
private:
    Ui::PowerSupplyWidget *ui;
    OperationConfirmationDialog *ocd;
    QString text;
private slots:
    void cancel();
    void StartSystem();
    void ShutDownSystem();
    void clicked_on();//点击开启按钮
    void clicked_off();//点击关闭按钮
signals:
    void cancel_signal();//点击返回
};

#endif // POWERSUPPLYWIDGET_H
