#ifndef CHENGEACCOUNT_H
#define CHENGEACCOUNT_H

#include <QMainWindow>
#include <QMessageBox>
#include "user.h"

namespace Ui
{
    class chengeAccount;
}

class chengeAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit chengeAccount(User *myUser, QWidget *parent = nullptr);
    ~chengeAccount();

private slots:
    void on_pushButton_clicked();

private:
    Ui::chengeAccount *ui;

    User *myUser;
};

#endif // CHENGEACCOUNT_H
