#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_pushButton_clicked() // кнопка "Подключиться"
{
    db = QSqlDatabase::addDatabase("QODBC"); // драйвер

    db.setDatabaseName("DRIVER={SQL Server}; Server="+ui->lineEdit->text()+";DATABASE="+ui->lineEdit_2->text()+";"); // формируем строку подключения

    db.setUserName(ui->lineEdit_3->text()); // логин
    db.setPassword(ui->lineEdit_4->text()); // пароль

    msg = new QMessageBox(); // вывод сообщения

    if (db.open()) {
        msg->setText("Соединение установлено");
    }
    else {
        msg->setText("Соединение НЕ установлено");
    }
    msg->show();
}

