#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include "user.h"

namespace Ui {
class withdraw;
}

class withdraw : public QMainWindow
{
    Q_OBJECT

public:
    explicit withdraw(User*myUser ,QWidget *parent = nullptr);
    ~withdraw();

private slots:
    void on_pushButton_Withdraw_clicked();

    void on_pushButton_Charge_clicked();

private:
    Ui::withdraw *ui;
    User*myUser;
};

#endif // WITHDRAW_H
