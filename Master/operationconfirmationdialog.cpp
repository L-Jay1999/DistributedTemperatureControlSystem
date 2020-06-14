﻿#include "operationconfirmationdialog.h"
#include "ui_operationconfirmationdialog.h"

OperationConfirmationDialog::OperationConfirmationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationConfirmationDialog)
{
    ui->setupUi(this);
    setWindowTitle("操作确认");
    setAttribute(Qt::WA_DeleteOnClose);//关闭时销毁
    setModal(true);//设置为模态
}

OperationConfirmationDialog::~OperationConfirmationDialog()
{
    delete ui;
}

void OperationConfirmationDialog::setText(QString text)
{
    text = QStringLiteral("将执行操作:\n\n") + text + QStringLiteral("\n\n是否确认？");
    ui->textEdit->setText(text);
    ui->textEdit->setReadOnly(true);//设置为只读
}
