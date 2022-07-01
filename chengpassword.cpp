#include "chengpassword.h"
#include "ui_chengpassword.h"

chengPassword::chengPassword(User *myUser, QWidget *parent) : QMainWindow(parent),
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
    QString pereventPassword = ui->lineEdit_PereventPassword->text();
    QString confirmPassword = ui->lineEdit_confirm_password->text();
    QString password = ui->lineEdit_password->text();

    switch (this->myUser->chengePassword(pereventPassword,password, confirmPassword))
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
    case ePereventPassword:
        QMessageBox::critical(this, "Error", "Your prevent password is not correct!");
        break;
    default:
        QMessageBox::warning(this, "?", "?");
    }
}


void chengPassword::on_actionInformation_triggered()
{
    hide();
    this->CengeAccount = new chengeAccount(this->myUser, this);
    this->CengeAccount->show();
}


void chengPassword::on_actionPassword_triggered()
{
//    hide();
//    this->ChengPassword = new chengPassword(this->myUser, this);
//    this->ChengPassword->show();
}


void chengPassword::on_actionCharge_and_withdraw_money_triggered()
{
    hide();
    this->Withdraw = new withdraw(this->myUser, this);
    this->Withdraw->show();
}


void chengPassword::on_actionSign_out_triggered()
{
    this->myUser->logout();
    hide();
    this->mainWindow = new MainWindow(this->myUser, this);
    this->mainWindow->show();
}


void chengPassword::on_actionExit_triggered()
{
    close();
}


void chengPassword::on_actionStock_triggered()
{
    hide();
    this->basicWindow = new BasicWindow(this->myUser, this);
    this->basicWindow->show();
}


