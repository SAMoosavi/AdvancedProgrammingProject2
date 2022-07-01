#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow( QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    switch (this->myUser->login(username, password))
    {
    case logined:
        if (this->myUser->accountIsSet())
        {
            QMessageBox::information(this, "Welcome!", "Welcome!");
            this->deleteUserClass();
            hide();
            this->basicWindow = new BasicWindow(this);
            this->basicWindow->show();
        }
        else
        {
            QMessageBox::information(this, "Welcome!", "Please complete your information!");
            this->deleteUserClass();
            hide();
            this->setAccount = new SetAccount(this);
            this->setAccount->show();
        }
        break;
    case notFuond:
        QMessageBox::critical(this, "Error!", "Username not found!");
        break;
    case notCorrectPassword:
        QMessageBox::critical(this, "Error!", "Password is not correct!");
        break;
    default:
        QMessageBox::information(this, "default", ":)");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    this->deleteUserClass();
    hide();
    this->registerFile = new RegisterFile(this);
    this->registerFile->show();
}

void MainWindow::deleteUserClass()
{
delete this->myUser;
    this->myUser=0;
}
