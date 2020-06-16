#include "detailwidget.h"
#include "ui_detailwidget.h"
#include <windows.h>

DetailWidget::DetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailWidget)
{
    ui->setupUi(this);
    setWindowTitle("详单查询");
//    ui->dateTimeEdit_end->setDateTime(QDateTime::currentDateTime().addSecs(30));
    ui->dateTimeEdit_end->setCalendarPopup(true);
//    ui->dateTimeEdit_begin->setDateTime(QDateTime::currentDateTime().addDays(-1));
    ui->dateTimeEdit_begin->setCalendarPopup(true);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"房间号"<<"开始时间"<<"结束时间"<<"风速"<<"风量消耗");
    connect(ui->pushButton_confirm,&QPushButton::clicked,this,&DetailWidget::GetDetails);
    connect(ui->pushButton_download,&QPushButton::clicked,this,&DetailWidget::DownLoad);
    connect(ui->pushButton_cancel,&QPushButton::clicked,this,&DetailWidget::Cancel);
}

DetailWidget::~DetailWidget()
{
    delete ui;
}

QString getLevel(struct StatPayload &sp)//获得风速
{
    switch (sp.speed_level) {
    case SpeedLevel::LOW:
        return "低";
        break;
    case SpeedLevel::MID:
        return "中";
        break;
    case SpeedLevel::HIGH:
        return "高";
        break;
    default:
        break;
    }
}

void DetailWidget::GetDetails()
{
    _begin = ui->dateTimeEdit_begin->dateTime();
    _end = ui->dateTimeEdit_end->dateTime();
    std::pair<bool,std::vector<StatPayload>> res = _report.getDetails(_begin,_end);
    if(res.first == true)
    {
        std::vector<StatPayload> &rep = res.second;
        ui->tableWidget->setRowCount(rep.size());
        for(int i = 0; i < rep.size(); i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(rep[i].room_id));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(rep[i].start_time.toString("yyyy-MM-dd hh:mm:ss")));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(rep[i].end_time.toString("yyyy-MM-dd hh:mm:ss")));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(getLevel(rep[i])));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(rep[i].cost/5)));
        }
    }
}

void DetailWidget::DownLoad()
{
    GetDetails();
    QString message = "开始时间：<font color='red'>" + _begin.toString("yyyy-MM-dd hh:mm:ss") + "</font><br>结束时间：<font color='red'>" + _end.toString("yyyy-MM-dd hh:mm:ss") + "</font><br>是否确认？";
    QMessageBox::StandardButton mb1 = QMessageBox::question(NULL,"导出确认",message,QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(mb1 == QMessageBox::Yes)
    {
        using namespace std;
        string command = "mkdir detail";
        system(command.c_str());
        string path = ".\\detail\\" + _begin.toString("yyyy-MM-dd-hh.mm.ss").toStdString() + '_' + _end.toString("yyyy-MM-dd-hh.mm.ss").toStdString() + ".csv";
        ofstream outf;
        outf.open(path,ios::out);
        if(outf.is_open())
        {
            outf << "Room ID" << ',' << "Begin Time" << ',' << "End Time" << ',' << "Wind Level" << ',' << "Power consumption" << endl;
            for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            {
                outf << ui->tableWidget->item(i,0)->text().toStdString() << ','
                     << ui->tableWidget->item(i,1)->text().toStdString() << ','
                     << ui->tableWidget->item(i,2)->text().toStdString() << ','
                     << ui->tableWidget->item(i,3)->text().toStdString() << ','
                     << ui->tableWidget->item(i,4)->text().toStdString() << endl;
            }
            outf.close();
            message = "导出成功";
        }else
        {
            message = "导出失败：文件无法生成";
        }
        QMessageBox::about(NULL,"提示",message);

    }

}

void DetailWidget::Cancel()
{
    this->hide();
}

void DetailWidget::UpdateTime()
{
    ui->dateTimeEdit_end->setDateTime(QDateTime::currentDateTime().addSecs(30));
    ui->dateTimeEdit_begin->setDateTime(QDateTime::currentDateTime().addDays(-1));
}
