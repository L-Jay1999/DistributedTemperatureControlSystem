#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H


#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QTableView>
#include <QHeaderView>

namespace Ui {
class MonitorWidget;
}

class MonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorWidget(QWidget *parent = nullptr);
//    ~MonitorWidget();
    void createView();

private:
    Ui::MonitorWidget *ui;

    QPushButton *testBtn;
    QPushButton *m_PushButton;
    QVBoxLayout *mainLayout;
//    QTreeView *treeView;
    QStandardItemModel *standItemModel;
    QTableView *tableView;
};

#endif // MONITORWIDGET_H
