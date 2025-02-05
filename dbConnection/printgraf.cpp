#include "printgraf.h"
#include "ui_printgraf.h"
#include <QSqlQuery>

printGraf::printGraf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::printGraf)
{
    ui->setupUi(this);
    ui -> setupUi(this);

    // заголовки графа
    ui -> widget -> plotLayout() -> insertRow(0);
    ui -> widget -> plotLayout() -> addElement(0, 0, new QCPPlotTitle(ui -> widget, "График выручки"));

    // инициализируем данные
    QVector <double> dx, dy;
    double minX, maxX, minY, maxY;
    minX = 0;
    minY = 0;
    maxX = 0;
    maxY = 0;

    // извлекаем данные из бд
    QSqlQuery *query = new QSqlQuery();
    if (query -> exec("SELECT * FROM chart")) {
        //определение границ графа
        while (query -> next()) {
            if (minX>=query->value(0).toDouble())
            minX = query->value(0).toDouble();
            if (minY>=query->value(1).toDouble())
            minY = query->value(1).toDouble();
            if (maxX<=query->value(0).toDouble())
            maxX = query->value(0).toDouble();
            if (maxY<=query->value(1).toDouble())
            maxY = query->value(1).toDouble();

            //добавляем оси Х и У
            dx << query -> value(0).toDouble();
            dy << query -> value(1).toDouble();
        }
        // построение графика
        QCPBars *bar = new QCPBars(ui -> widget -> xAxis, ui -> widget -> yAxis);
        bar -> setName("Значение");
        bar -> setBrush(QColor(255,0,0,255)); // цвет заливки графика (R,G,B,Transparency)
        bar -> setData(dx,dy); //координаты точек
        bar -> setWidth(0.25); //толщина линий

        // добавляем подписей осей
        ui->widget->xAxis->setLabel("Месяц");
        ui->widget->yAxis->setLabel("Выручка");
        // устанавливаем границы отображения графика
        ui->widget->xAxis->setRange(minX,maxX+0.20);
        ui->widget->yAxis->setRange(minY,maxY+1);
        // запрещаем автоматичи определять шаг шкалы
        ui->widget->xAxis->setAutoTickStep(false);
        ui->widget->yAxis->setAutoTickStep(false);
        // устанавливаем шаг вручную
        ui->widget->xAxis->setTickStep(1);
        ui->widget->yAxis->setTickStep(5);

    }
}

printGraf::~printGraf()
{
    delete ui;
}

