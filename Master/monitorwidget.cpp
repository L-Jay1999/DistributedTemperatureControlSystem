#include "monitorwidget.h"

MonitorWidget::MonitorWidget(QWidget *parent) :
    QWidget(parent)
{
    createView();
}

void MonitorWidget::createView()
{
    mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(10);
        mainLayout->setMargin(10);

        tableView = new QTableView(this);
        standItemModel = new QStandardItemModel(this);

        standItemModel->setColumnCount(5);
        standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("房间号"));
        standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("开关状态"));
        standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("当前温度"));
        standItemModel->setHeaderData(3,Qt::Horizontal,QStringLiteral("送风状态"));
        standItemModel->setHeaderData(4,Qt::Horizontal,QStringLiteral("当前风速"));

        //TODO 从DBAccess中拿到所有房间的数据
        QDateTime begin, end;
        begin.setDate(QDate::currentDate());
        end.setDate(QDate::currentDate().addDays(1));
        std::pair<bool, std::vector<StatPayload>> response = db.getRoomRequestStats(begin,end);//获取当日报表
//        for(auto i=response.second.begin();i!=response.second.end())
//        {
//            QStandardItem *standItem1 = new QStandardItem(tr(i->room_id).arg(i+1));
//            QStandardItem *standItem2 = new QStandardItem(tr("line %1").arg(i+1));
//            standItemModel->setItem(i,0,standItem1);
//            standItemModel->item(i,0)->setForeground(QBrush(QColor(255,0,0)));
//            standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);
//            standItemModel->setItem(i,1,standItem2);
//            standItemModel->setItem(i,2,standItem2);


//        }
        for(auto it = response.second.begin(); it != response.second.end();)
        {
            int i = 0;
            QString room_id = it->room_id;
            const char *c_roomid = room_id.toLocal8Bit().data();
            QDateTime room_endtime = it->end_time;
            QDateTime room_starttime = it->start_time;

            QStandardItem *standItem1 = new QStandardItem(tr(c_roomid).arg(i+1));
            standItemModel->setItem(i,0,standItem1);
            it++;
            i++;
        }

        tableView->setModel(standItemModel);

        //设置表格属性
        tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
        tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
        tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);

        tableView->setColumnWidth(0,100);
        tableView->setColumnWidth(1,200);
        tableView->setColumnWidth(2, 200);
        tableView->setColumnWidth(3, 200);
        tableView->setColumnWidth(4, 200);

        tableView->verticalHeader()->hide();    //隐藏默认显示的行头
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setShowGrid(false);

        mainLayout->addWidget(tableView);
        this->setLayout(mainLayout);
}

