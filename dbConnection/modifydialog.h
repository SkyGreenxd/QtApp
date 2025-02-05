#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <QWidget>

namespace Ui {
class ModifyDialog;
}

class ModifyDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyDialog(QWidget *parent = nullptr);
    ~ModifyDialog();

private slots:
    void on_pushButton_clicked();
    void sendingID(int);

    void on_toolButton_clicked();

private:
    Ui::ModifyDialog *ui;
    int tempID;
    QString Img;
};

#endif // MODIFYDIALOG_H
