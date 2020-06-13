#ifndef STANDBYWIDGET_H
#define STANDBYWIDGET_H

#include <QWidget>
#include "managerloginwidget.h"
#include "managercontrolpanel.h"

namespace Ui {
class StandbyWidget;
}

class StandbyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StandbyWidget(QWidget *parent = 0);
    ~StandbyWidget();

private:
    Ui::StandbyWidget *ui;
    ManagerLoginWidget *mlw;
    ManagerControlPanel *mcp;
private slots:
    void switch_to_login();//切换到认证界面
    void reshow();//认证失败，切回等待界面
    void switch_to_panel(const QString &manager_account);//认证成功，切换到控制面板
signals:
};
#endif // STANDBYWIDGET_H
