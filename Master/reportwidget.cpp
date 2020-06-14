#include "reportwidget.h"
#include "report.h"
ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "!!!report widget";
    createReportView();
}

void ReportWidget::createReportView()
{
        qDebug() << "!!!report widget";
        mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(10);
        mainLayout->setMargin(10);

        tableView = new QTableView(this);
        standItemModel = new QStandardItemModel(this);

        standItemModel->setColumnCount(5);
        standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("房间号"));
        standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("从控机开关机次数"));
        standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("温控请求起止时间"));
        standItemModel->setHeaderData(3,Qt::Horizontal,QStringLiteral("温控请求起止温度及风量消耗"));
        standItemModel->setHeaderData(4,Qt::Horizontal,QStringLiteral("当日总费用"));

        //增加按钮及相关数据
        const QDate today = QDate::currentDate();
        std::pair<bool, std::vector<StatPayload>> response = Report::getTodayReport(today);
        int i = 0;
        for(auto it = response.second.begin(); it != response.second.end();it ++)
        {
            download_btn = new QPushButton(this);
            connect(download_btn, SIGNAL(clicked(bool)), this, SLOT(ClickDownloadButton()));
            download_btn->setProperty("row", i);
            tableView->setIndexWidget(standItemModel->index(standItemModel->rowCount() - 1, 5), download_btn);//每个房间单设置下载日表
            i++;
        }
        download_btn = new QPushButton(this);
        connect(download_btn, SIGNAL(clicked(bool)), this, SLOT(ClickDownloadButton()));
        download_btn->setProperty("row", i);
        tableView->setIndexWidget(standItemModel->index(standItemModel->rowCount() - 1, 0), download_btn);
        //最后一行单加总下载

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
        tableView->setColumnWidth(1,300);
        tableView->setColumnWidth(2, 300);
        tableView->setColumnWidth(3, 300);
        tableView->setColumnWidth(4, 300);

        tableView->verticalHeader()->hide();    //隐藏默认显示的行头
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setShowGrid(false);

        mainLayout->addWidget(tableView);
        this->setLayout(mainLayout);
}

