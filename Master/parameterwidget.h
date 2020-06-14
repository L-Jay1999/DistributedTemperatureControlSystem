#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H
#include <QWidget>
#include<QDebug>

namespace Ui {
class ParameterWidget;
}

class ParameterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterWidget(QWidget *parent = nullptr);
    ~ParameterWidget();
    int getTemperature();
    QString getMode();
//    WorkingMode _mode;

private:
    Ui::ParameterWidget *ui;
    int temperature = 0;
    QString mode = "cold";


private slots:
    void cancel();
    void confirm();
signals:
    void cancel_signal();//点击返回
    void confirm_signal();//设置返回
};

#endif // PARAMETERWIDGET_H
