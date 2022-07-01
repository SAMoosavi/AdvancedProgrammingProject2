#ifndef SETACCOUNT_H
#define SETACCOUNT_H

#include <QMainWindow>
#include "user.h"
#include <QString>
#include <QMessageBox>
#include "basicwindow.h"

class BasicWindow;

namespace Ui
{
    class SetAccount;
}

class SetAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetAccount(QWidget *parent = nullptr);
    ~SetAccount();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SetAccount *ui;
    User *myUser = new User();
    BasicWindow *basicWindow;
    void deleteUserClass();
};

#endif // SETACCOUNT_H
