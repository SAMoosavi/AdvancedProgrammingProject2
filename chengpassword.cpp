#include "chengpassword.h"
#include "ui_chengpassword.h"

chengPassword::chengPassword(User *myUser,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chengPassword)
{
    ui->setupUi(this);
    this->myUser = myUser;
}

chengPassword::~chengPassword()
{
    delete ui;
}

void chengPassword::on_pushButton_clicked()
{
    QString confirmPassword = ui->lineEdit_confirm_password->text();
    QString password = ui->lineEdit_password->text();

    switch (this->myUser->chengePassword(password, confirmPassword))
    {
    case chengedPassword:
        QMessageBox::information(this, "Chenge Password", "Your password chenged.");
        break;
    case eVPassword:
        QMessageBox::critical(this, "Error", "Your password is not strong enough!");
        break;
    case eConfirmPassword:
        QMessageBox::critical(this, "Error", "Your confirm password is not correct!");
        break;
    default:
        QMessageBox::warning(this, "?", "?");
    }
}

