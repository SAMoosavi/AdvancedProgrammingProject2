#ifndef CHENGPASSWORD_H
#define CHENGPASSWORD_H

#include <QMainWindow>
#include <QMessageBox>
#include "user.h"
#include "chengeaccount.h"
#include "basicwindow.h"
#include "withdraw.h"
#include "mainwindow.h"

class chengeAccount;
class BasicWindow;
class withdraw;
class MainWindow;

namespace Ui
{
    class chengPassword;
}

class chengPassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit chengPassword(User *myUser, QWidget *parent = nullptr);
    ~chengPassword();

private slots:
    void on_pushButton_clicked();

    void on_actionStock_triggered();

    void on_actionInformation_triggered();

    void on_actionPassword_triggered();

    void on_actionCharge_and_withdraw_money_triggered();

    void on_actionSign_out_triggered();

    void on_actionExit_triggered();

private:
    Ui::chengPassword *ui;

    User *myUser;
    chengeAccount *CengeAccount;
    chengPassword *ChengPassword;
    withdraw *Withdraw;
    MainWindow *mainWindow;
    BasicWindow *basicWindow;
};

#endif // CHENGPASSWORD_H
