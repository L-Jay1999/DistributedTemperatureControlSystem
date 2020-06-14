#ifndef OPERATIONCONFIRMATIONDIALOG_H
#define OPERATIONCONFIRMATIONDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class OperationConfirmationDialog;
}

class OperationConfirmationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OperationConfirmationDialog(QWidget *parent = 0);
    ~OperationConfirmationDialog();
    void setText(QString);

private:
    Ui::OperationConfirmationDialog *ui;

};

#endif // OPERATIONCONFIRMATIONDIALOG_H
