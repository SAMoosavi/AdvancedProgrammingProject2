#ifndef CHENGEACCOUNT_H
#define CHENGEACCOUNT_H

#include <QMainWindow>
#include <QMessageBox>
#include "user.h"
#include "chengpassword.h"
#include "withdraw.h"
#include "mainwindow.h"
#include "basicwindow.h"

class chengPassword;
class withdraw;
class MainWindow;
class BasicWindow;

namespace Ui
{
    class chengeAccount;
}

class chengeAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit chengeAccount( QWidget *parent = nullptr);
    ~chengeAccount();

private slots:
    void on_pushButton_clicked();

    void on_actionstock_triggered();

    void on_actionInformation_triggered();

    void on_actionPassword_triggered();

    void on_actionCharge_and_triggered();

    void on_actionSing_out_triggered();

    void on_actionExit_triggered();

private:
    Ui::chengeAccount *ui;

   User *myUser = new User();
    chengeAccount *ChangeAccount;
    chengPassword *changePassword;
    withdraw *Withdraw;
    MainWindow *mainWindow;
    BasicWindow *basicWindow;
    void deleteUserClass();
};

#endif // CHENGEACCOUNT_H
