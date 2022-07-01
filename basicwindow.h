#ifndef BASICWINDOW_H
#define BASICWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "chengeaccount.h"

class chengeAccount;

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

private:
    Ui::BasicWindow *ui;
    User *myUser;
    chengeAccount *CengeAccount;
};

#endif // BASICWINDOW_H
