#ifndef SETACCOUNT_H
#define SETACCOUNT_H

#include <QMainWindow>
#include "user.h"
#include <QString>
#include <QMessageBox>

namespace Ui {
class SetAccount;
}

class SetAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetAccount(User *myUser,QWidget *parent = nullptr);
    ~SetAccount();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SetAccount *ui;
    User *myUser;
};

#endif // SETACCOUNT_H
