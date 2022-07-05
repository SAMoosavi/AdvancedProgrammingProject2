#include "chengpassword.h"
#include "ui_chengpassword.h"

chengPassword::chengPassword(QWidget *parent) : QMainWindow(parent),
                                                              ui(new Ui::chengPassword)
{
    ui->setupUi(this);
}

chengPassword::~chengPassword()
{
    delete ui;
}

// push change button
void chengPassword::on_pushButton_clicked()
{
    QString pereventPassword = ui->lineEdit_PereventPassword->text();
    QString confirmPassword = ui->lineEdit_confirm_password->text();
    QString password = ui->lineEdit_password->text();

    // use changePassword function in User class
    switch (this->myUser->changePassword(pereventPassword,password, confirmPassword))
    {
    case changedPassword:
        ui->lineEdit_PereventPassword->setText("");
        ui->lineEdit_confirm_password->setText("");
        ui->lineEdit_password->setText("");
        QMessageBox::information(this, "Change Password", "Your password changed.");
        break;
    case eVPassword:
        QMessageBox::critical(this, "Error", "Your password is not strong enough!");
        break;
    case eConfirmPassword:
        QMessageBox::critical(this, "Error", "Your confirm password is not correct!");
        break;
    case ePereventPassword:
        QMessageBox::critical(this, "Error", "Your previous password is not correct!");
        break;
    default:
        QMessageBox::warning(this, "?", "?");
    }
}

// choose change information
void chengPassword::on_actionInformation_triggered()
{
    this->deleteUserClass();
    hide();
    this->ChangeAccount = new chengeAccount(this);
    this->ChangeAccount->show();
}

// choose change password
void chengPassword::on_actionPassword_triggered(){}

// choose charge and withdraw money
void chengPassword::on_actionCharge_and_withdraw_money_triggered()
{
    this->deleteUserClass();
    hide();
    this->Withdraw = new withdraw(this);
    this->Withdraw->show();
}

// choose sign out
void chengPassword::on_actionSign_out_triggered()
{
    this->myUser->logout();
    this->deleteUserClass();
    hide();
    this->mainWindow = new MainWindow(this);
    this->mainWindow->show();
}

// choose exit
void chengPassword::on_actionExit_triggered()
{
    close();
}

// choose buy, sale and show stocks
void chengPassword::on_actionStock_triggered()
{
    this->deleteUserClass();
    hide();
    this->basicWindow = new BasicWindow(this);
    this->basicWindow->show();
}

// delete the User object
void chengPassword::deleteUserClass()
{
    delete this->myUser;
    this->myUser = 0;
}
