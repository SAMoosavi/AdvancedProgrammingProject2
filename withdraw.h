#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include "user.h"
#include "chengeaccount.h"
#include "chengpassword.h"
#include "basicwindow.h"
#include "mainwindow.h"

class chengeAccount;
class chengPassword;
class BasicWindow;
class MainWindow;

namespace Ui
{
    class withdraw;
}

class withdraw : public QMainWindow
{
    Q_OBJECT

public:
    explicit withdraw(User *myUser, QWidget *parent = nullptr);
    ~withdraw();

private slots:
    void on_pushButton_Withdraw_clicked();

    void on_pushButton_Charge_clicked();

    void on_actionStock_triggered();

    void on_actionInformation_triggered();

    void on_actionPassword_triggered();

    void on_actionCharge_and_withdraw_money_triggered();

    void on_actionSign_out_triggered();

    void on_actionExit_triggered();

private:
    Ui::withdraw *ui;
    User *myUser;
    chengeAccount *CengeAccount;
    chengPassword *ChengPassword;
    withdraw *Withdraw;
    MainWindow *mainWindow;
    BasicWindow *basicWindow;
};

#endif // WITHDRAW_H
