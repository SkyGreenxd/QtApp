#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();
    QMessageBox *msg;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ConnectionDialog *ui;
    QSqlDatabase db;
};

#endif // CONNECTIONDIALOG_H
