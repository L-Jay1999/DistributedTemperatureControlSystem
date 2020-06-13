#ifndef USERMANAGEMENTWIDGET_H
#define USERMANAGEMENTWIDGET_H

#include <QWidget>
#include <QDateTime>
#include "promptdialog.h"

namespace Ui {
class UserManagementWidget;
}

class UserManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserManagementWidget(QWidget *parent = 0);
    ~UserManagementWidget();
    void Add();     //添加房客
    void Delete();  //删除房客
    void Refresh(); //刷新房客信息
    void Clear();   //清空输入信息
    void Close();   //关闭界面

private:
    Ui::UserManagementWidget *ui;
    PromptDialog *pd;
    QString _UserList;          //房客信息
    QString _RoomID;            //房间ID
    QString _UserID;            //用户ID
    QDateTime _EffDateTime;     //有效时间
    QDateTime _CurDateTime;     //系统时间
    QString _PromptText;        //提示信息

signals:
    void cancel_signal();

};

#endif // USERMANAGEMENTWIDGET_H