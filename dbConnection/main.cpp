#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) // отображение главного окна
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
