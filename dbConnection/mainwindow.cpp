#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fl = 0;

    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(CustomMenuReq(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered() // "Подключение" -> "Подключиться к бд"
{
    dlg = new ConnectionDialog(); //создание диалогового окна
    dlg->show(); //показ окна
}


void MainWindow::on_pushButton_clicked() // кнопка "Обновление"
{
    qmodel = new QSqlQueryModel();
    qmodel->setQuery("SELECT a.ID, a.name, b.name, a.ImagePath, a.prodDate  FROM products a inner join category b  ON a.catID = b.id;");
    ui -> tableView -> setModel(qmodel); //tableView вставляет модель qmodel в себя
    fl = 1; // флаг состояния
}

void MainWindow::on_pushButton_2_clicked() // кнопка "Добавить"
{
    add = new AddDialog();
    add->show();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) // захват клика по таблице
{
    int temp_ID;
    temp_ID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt(); // сохр ID в temp_ID

    //запрос для получения данных записи
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, catID, ImagePath, prodDate FROM products WHERE ID=:ID");
    query->bindValue(":ID",temp_ID);

    ui->lineEdit->setText(QString::number(temp_ID)); // установка значения в lineEdit

    if(query->exec()){ // выполнение запроса
        query->next();
        ui->lineEdit_2->setText(query->value(0).toString());

        QSqlQuery *queryCombo = new QSqlQuery();
        queryCombo->exec("SELECT name FROM category");
        ui->comboBox->clear();
        while (queryCombo->next()){
            ui->comboBox->addItem(queryCombo->value(0).toString());
        }
        ui->comboBox->setCurrentIndex(query->value(1).toInt()-1);

        Img = query -> value(2).toString();
        ui -> label_4 -> setPixmap(Img);
        ui -> label_4 -> setScaledContents(true);

        ui->dateEdit->setDate(query->value(3).toDate());
    }
}


void MainWindow::on_pushButton_4_clicked() // удаление строки
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM products WHERE ID=:ID");
    query->bindValue(":ID", ui->lineEdit->text());
    query->exec();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->clear();
    ui->label_4->clear();
    ui->dateEdit->setDate(QDate(2000,1,1));

    MainWindow::on_pushButton_clicked();
}


void MainWindow::on_pushButton_3_clicked() // изменение строки
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE products SET name = :name, catID = :category, ImagePath = :image, prodDate = :proddate WHERE ID = :ID");
    query->bindValue(":name", ui->lineEdit_2->text());

    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT name FROM category");
    while (queryCombo->next()){
        ui->comboBox->addItem(queryCombo->value(0).toString());
    }
    query->bindValue(":category", ui->comboBox->currentIndex()+1);
    query->bindValue(":ID", ui->lineEdit->text());
    query->bindValue(":image", Img);
    query->bindValue(":proddate", ui->dateEdit->text());
    query->exec();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->clear();
    ui->label_4->clear();
    ui->dateEdit->setDate(QDate(2000,1,1));

    MainWindow::on_pushButton_clicked();
}

void MainWindow::CustomMenuReq(QPoint pos) { // Контекстное меню
    if (fl == 1){
        QModelIndex index = ui->tableView->indexAt(pos); // Получение индекса элемента
        GlobID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt(); // в GlobID помещается ID
        QMenu *menu = new QMenu();
        QAction *ModRec = new QAction("Изменить...", this);
        QAction *DelRec = new QAction("Удалить...", this);

        // Соединение сигналов и слотов
        connect(ModRec, SIGNAL(triggered()), this, SLOT(ModRecAction()));
        connect(DelRec, SIGNAL(triggered()), this, SLOT(DelRecAction()));

        menu->addAction(ModRec);
        menu->addAction(DelRec);

        menu->popup(ui->tableView->viewport()->mapToGlobal(pos)); // Отображение контекстного меню
    }
}

void MainWindow::DelRecAction() { // Удаление пкм
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM products WHERE ID = :ID");
    query->bindValue(":ID", GlobID);
    query->exec();
    MainWindow::on_pushButton_clicked();
}

void MainWindow::ModRecAction(){ // Изменение пкм
    mdlg = new ModifyDialog();
    connect(this, SIGNAL(sendID(int)), mdlg, SLOT(sendingID(int))); // Соединение сигнала и слота
    emit sendID(GlobID);
    mdlg->show();
    disconnect(this, SIGNAL(sendID(int)), mdlg, SLOT(sendingID(int))); // отключение сигнала и слота
}




void MainWindow::on_pushButton_5_clicked() // Экспорт в Word
{
    pdlg = new PrintDialog();
    pdlg->show();
}


void MainWindow::on_pushButton_6_clicked() // Экспорт в PDF
{
    // создание строки html и добавление таблицы
    QString str;
    str.append("<html><head></head><body><center>"
    +QString("Пример создания отчёта"));
    str.append("<table border=1><tr>");
    str.append("<td>"+QString("ID")+"</td>");
    str.append("<td>"+QString("Наименование")+"</td>");
    str.append("<td>"+QString("Категория")+"</td>");
    str.append("<td>"+QString("Путь до изображения")+"</td>");
    str.append("<td>"+QString("Дата получения")+"</td></tr>");
    // бд
    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT a.ID, a.name, b.name, a.ImagePath, a.prodDate  FROM products a inner join category b  ON a.catID = b.id;");

    // добавление строк бд в таблицу html
    while (query->next()) {
        str.append("<tr><td>"+QString(query->value(0).toString())+"</td>");
        str.append("<td>"+QString(query->value(1).toString())+"</td>");
        str.append("<td>"+QString(query->value(2).toString())+"</td>");
        str.append("<td>"+QString(query->value(3).toString())+"</td>");
        str.append("<td>"+QString(query->value(4).toString())+"</td></tr>");
    }
    str.append("</table></center></body></html>");

    // создание pdf
    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    // путь сохранения
    QString path =
    QFileDialog::getSaveFileName(NULL,"Сохранить","Отчёт","PDF(*.pdf)");
    if (path.isEmpty()) return;
    printer.setOutputFileName(path);

    // загрузка html в pdf
    QTextDocument doc;
    doc.setHtml(str);
    doc.print(&printer);
}


void MainWindow::on_toolButton_clicked() // Кнопка "..."
{
    Img = QFileDialog::getOpenFileName(0, "Открыть файл", Img, "*.jpg");
    ui -> label_4 -> setPixmap(Img);
    ui -> label_4 -> setScaledContents(true);
}


void MainWindow::on_action_2_triggered() // Отчет -> Граф
{
    pg = new printGraf();
    pg->show();
}

