#ifndef USERLOGINDIALOG_H
#define USERLOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QWidget>
#include <QMessageBox>
#include <tuple>

#include "logincontroller.h"
#include "user.h"

#include "common.h"
#include "./listener.h"

namespace Ui {
class UserLoginDialog;
}

class UserLoginDialog : public QDialog
{
    Q_OBJECT
    Q_ENUM(WorkingMode)
public:
    explicit UserLoginDialog(QWidget *parent = nullptr);
    ~UserLoginDialog();

signals:
    void LoginSuccess(const QString &room_id, const QString &_id, WorkingMode mode, double init_temp);
    void StartListen();
    void StopListen();
private slots:
    void on_quitbutton_clicked();

    void on_confirmbutton_clicked();

private:
    QThread *_thread;
    Ui::UserLoginDialog *ui;
    Listener * _listener;
    QLineEdit *_id_input;
    QLineEdit *_room_id_input;
};

#endif // USERLOGINDIALOG_H
