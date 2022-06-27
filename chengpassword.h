#ifndef CHENGPASSWORD_H
#define CHENGPASSWORD_H

#include <QMainWindow>
#include <QMessageBox>
#include "user.h"

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

private:
    Ui::chengPassword *ui;

    User *myUser;
};

#endif // CHENGPASSWORD_H
