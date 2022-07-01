#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "registerfile.h"
#include "setaccount.h"
#include "basicwindow.h"

class RegisterFile;
class BasicWindow;
class SetAccount;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    User *myUser = new User();
    RegisterFile *registerFile;
    SetAccount *setAccount;
    BasicWindow *basicWindow;
    void deleteUserClass();
};
#endif // MAINWINDOW_H
