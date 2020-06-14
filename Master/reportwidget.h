#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>

#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QTableView>
#include <QHeaderView>
#include <QDateTime>
#include "global.h"
#include "report.h"
#include <map>
#include <utility>

namespace Ui {
class ReportWidget;
}

class ReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWidget(QWidget *parent = nullptr);
    void createReportView();

private:
    Ui::ReportWidget *ui;
//    Sensor sensor;
    QPushButton *m_PushButton;
    QVBoxLayout *mainLayout;
//    QTreeView *treeView;
    QStandardItemModel *standItemModel;
    QTableView *tableView;
    QPushButton *download_btn;
    DBAccess db;
};

#endif // REPORTWIDGET_H
