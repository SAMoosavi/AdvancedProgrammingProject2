#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <QMainWindow>
#include "user.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class RegisterFile;
}

class RegisterFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterFile(User*myUser ,QWidget *parent = nullptr);
    ~RegisterFile();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RegisterFile *ui;
    User* myUser;
    MainWindow* mainWindow;
};

#endif // REGISTERFILE_H
