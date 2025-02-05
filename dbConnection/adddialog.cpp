#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT name FROM category");
    while (queryCombo->next()){
        ui->comboBox->addItem(queryCombo->value(0).toString()); // заполнение комбобокса
    }

    ui->dateEdit->setDate(QDate::currentDate());
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_pushButton_clicked() // кнопка "Добавить"
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("INSERT INTO products (name, catID, ImagePath, prodDate) VALUES (:name, :cat_ID, :ImagePath, :date)"); // запрос на вставку данных в таблицу
    query->bindValue(":name",ui->lineEdit->text());
    query->bindValue(":cat_ID",ui->comboBox->currentIndex()+1);
    query->bindValue(":ImagePath", Img);
    query->bindValue(":date", ui->dateEdit->text());
    QMessageBox *mes = new QMessageBox();
    if(!query->exec()){
        mes->setText("Запрос составлен неверно!");
        mes->show();
    }
    else {
        close();
    }
}


void AddDialog::on_toolButton_clicked() // кнопка "..."
{
    Img = QFileDialog::getOpenFileName(0,"Открыть файл", Img, "*.jpg");
    ui->label_3->setPixmap(Img);
    ui->label_3->setScaledContents(true);
}
