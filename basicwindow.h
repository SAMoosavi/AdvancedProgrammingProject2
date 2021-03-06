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
    explicit BasicWindow( QWidget *parent = nullptr);
    ~BasicWindow();
    void showAllStocks();
    void showStocks();
    void buyStock();
    void saleStock();

private slots:
    void on_pushButton_buy_clicked();

    void on_actionInformation_triggered();

    void on_actionPassword_triggered();

    void on_actionCharge_and_withdraw_money_triggered();

    void on_actionSign_out_triggered();

    void on_actionExit_triggered();

    void on_actionStock_triggered();

    void on_pushButton_sale_clicked();

private:
    Ui::BasicWindow *ui;
    User *myUser = new User();
    user *us;
    Stock *stock = new Stock();
    chengeAccount *CengeAccount;
    chengPassword *changePassword;
    withdraw *Withdraw;
    MainWindow *mainWindow;
    BasicWindow *basicWindow;
    void deleteUserClass();
};

#endif // BASICWINDOW_H
