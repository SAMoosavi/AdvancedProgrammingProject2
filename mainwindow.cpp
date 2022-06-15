#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(User *myUser, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->myUser = myUser;
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
        if(this->myUser->accountIsSet()){
            QMessageBox::information(this, "Welcome!", "Welcome!");
            // TODO: cheng page
        }
        else{
            QMessageBox::information(this, "Welcome!", "Please complete your information!");
            hide();
            this->setAccount = new SetAccount(this->myUser, this);
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
    hide();
    this->registerFile = new RegisterFile(this->myUser, this);
    this->registerFile->show();
}
