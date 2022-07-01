#ifndef BASICWINDOW_H
#define BASICWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "chengeaccount.h"
#include "chengpassword.h"
#include "withdraw.h"
#include "mainwindow.h"

class chengeAccount;
class chengPassword;
class withdraw;
class MainWindow;

namespace Ui {
class BasicWindow;
}

class BasicWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BasicWindow(User *myUser, QWidget *parent = nullptr);
    ~BasicWindow();
    void showAllStocks();
    void showStocks(user *us);
    void buyStock();

private slots:
    void on_pushButton_buy_clicked();

    void on_actionInformation_triggered();

    void on_actionPassword_triggered();

    void on_actionCharge_and_withdraw_money_triggered();

    void on_actionSign_out_triggered();

private:
    Ui::BasicWindow *ui;
    User *myUser;
    chengeAccount *CengeAccount;
    chengPassword *ChengPassword;
    withdraw *Withdraw;
    MainWindow *mainWindow;
};

#endif // BASICWINDOW_H
