#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QWidget>

namespace Ui {
class StartUpWindow;
}

class StartUpWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartUpWindow(QWidget *parent = nullptr);
    ~StartUpWindow();
public slots:
    void ShowUserLoginWidget();
private:
    Ui::StartUpWindow *ui;
};

#endif // STARTUPWINDOW_H
