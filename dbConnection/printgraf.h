#ifndef PRINTGRAF_H
#define PRINTGRAF_H

#include <QWidget>

namespace Ui {
class printGraf;
}

class printGraf : public QWidget
{
    Q_OBJECT

public:
    explicit printGraf(QWidget *parent = nullptr);
    ~printGraf();

private:
    Ui::printGraf *ui;
};

#endif // PRINTGRAF_H
