#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectiondialog.h"
#include "ui_connectiondialog.h"
// #include <QSqlTableModel>
#include "QSqlQueryModel"
#include "adddialog.h"
#include "ui_adddialog.h"
#include "modifydialog.h"
#include "ui_modifydialog.h"
#include "printdialog.h"
#include "ui_printdialog.h"
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include "printgraf.h"
#include "ui_printgraf.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int fl;
    int GlobID;

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void CustomMenuReq(QPoint);

    void DelRecAction();

    void ModRecAction();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_toolButton_clicked();

    void on_action_2_triggered();

signals:
    void sendID(int);

private:
    Ui::MainWindow *ui;
    ConnectionDialog *dlg;
    //QSqlTableModel *tmodel;
    QSqlQueryModel *qmodel;
    AddDialog *add;
    ModifyDialog *mdlg;
    PrintDialog *pdlg;
    QString Img;
    printGraf *pg;
};
#endif // MAINWINDOW_H
