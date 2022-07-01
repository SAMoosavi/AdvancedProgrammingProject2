#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <QMainWindow>
#include <QMessageBox>
#include "user.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui
{
    class RegisterFile;
}

class RegisterFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterFile(QWidget *parent = nullptr);
    ~RegisterFile();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RegisterFile *ui;
    User *myUser = new User();
    MainWindow *mainWindow;
    void goToSingnInPage();
    void deleteUserClass();
};

#endif // REGISTERFILE_H
