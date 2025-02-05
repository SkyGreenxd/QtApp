#include "modifydialog.h"
#include "ui_modifydialog.h"
#include "QSqlQuery"
#include "QFileDialog"

ModifyDialog::ModifyDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyDialog)
{
    ui->setupUi(this);
    ui -> label_3 -> setScaledContents(true);
    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo -> exec("SELECT name FROM category");
    while (queryCombo -> next())
    {
        ui -> comboBox -> addItem(queryCombo -> value(0).toString());
    }
}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}

void ModifyDialog::on_pushButton_clicked() // изменить
{
    QSqlQuery *query = new QSqlQuery;
    query->prepare("UPDATE products SET name =:name, catID =:category, ImagePath = :image, prodDate = :proddate where ID =:ID");
    query->bindValue(":ID", tempID);
    query->bindValue(":name", ui->lineEdit->text());
    query->bindValue(":category", ui->comboBox->currentIndex()+1);
    query->bindValue(":image",Img);
    query->bindValue(":proddate", ui->dateEdit->text());
    if (query->exec()){
        close();
    }

}

void ModifyDialog::sendingID(int aa){ // загрузка данных из бд для редактирования
    tempID = aa;

    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, catID, ImagePath, prodDate FROM products WHERE ID=?");
    query->bindValue(0, aa);

    if(query->exec()) { // заполнение
        query->next();
        ui->lineEdit->setText(query->value(0).toString()); // name ну и так далее

        ui->comboBox->setCurrentIndex(query->value(1).toInt()-1);

        Img = query -> value(2).toString();
        ui -> label_3 -> setPixmap(Img);

        ui->dateEdit->setDate(query->value(3).toDate());
    }
}


void ModifyDialog::on_toolButton_clicked()
{
    Img = QFileDialog::getOpenFileName(0,"Открыть файл", Img, "*.jpg");
    ui->label_3->setPixmap(Img);
    ui->label_3->setScaledContents(true);
}

