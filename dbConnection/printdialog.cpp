#include "printdialog.h"
#include "ui_printdialog.h"

PrintDialog::PrintDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintDialog)
{
    ui->setupUi(this);
}

PrintDialog::~PrintDialog()
{
    delete ui;
}

void PrintDialog::on_toolButton_clicked() // кнопка "..."
{
    ui -> lineEdit -> setText(QFileDialog::getOpenFileName(0, "Выберите файл", ".\\", "*.html"));
}


void PrintDialog::on_pushButton_clicked() // кнопка "Сформировать"
{
    // создание и открытие файла
    QFile *file = new QFile();
    file -> setFileName(ui -> lineEdit -> text());
    file -> open(QIODevice::WriteOnly);
    QTextStream in (file);

    // html
    in << "<html><head></head><body><center>"
          +QString("Пример создания отчета");
    in <<"<table border=1><tr>";
    in << "<td>"+QString("ID")+"</td>";
    in << "<td>"+QString("Наименование")+"</td>";
    in << "<td>"+QString("Категория")+"</td>";
    in << "<td>"+QString("Путь до изображения")+"</td>";
    in << "<td>"+QString("Дата получения")+"</td></tr>";

    QSqlQuery *query = new QSqlQuery();
    query -> exec("SELECT a.ID, a.name, b.name, a.ImagePath, a.prodDate  FROM products a inner join category b  ON a.catID = b.id");

    // заполняем html
    while (query->next()){
        in << "<tr><td>"+QString(query->value(0).toString())+"</td>";
        in << "<td>"+QString(query->value(1).toString())+"</td>";
        in << "<td>"+QString(query->value(2).toString())+"</td>";
        in << "<td>"+QString(query->value(3).toString())+"</td>";
        in << "<td>"+QString(query->value(4).toString())+"</td></tr>";
    }

    in << "</table></center></body></html>";
    file->close();

    // открываем в Word
    QAxObject *word = new QAxObject("Word.Application",this);
    word->setProperty("DisplayAlerts",false);
    word->setProperty("Visible", true);
    QAxObject *doc = word->querySubObject("Documents");
    doc->dynamicCall("Open(QVariant)", "D:\\PUPUPUPU\\pupu.html");
}

