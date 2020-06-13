#include "operationconfirmationdialog.h"
#include "ui_operationconfirmationdialog.h"

OperationConfirmationDialog::OperationConfirmationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationConfirmationDialog)
{
    ui->setupUi(this);
    setWindowTitle("Operation confirm");
    setAttribute(Qt::WA_DeleteOnClose);
}

OperationConfirmationDialog::~OperationConfirmationDialog()
{
    delete ui;
}

void OperationConfirmationDialog::setText(QString text)
{
    text = "We're going to operate:\n\n" + text + "\n\nConfirm?";
    ui->textEdit->setText(text);
}

