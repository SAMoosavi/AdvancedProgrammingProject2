#include "withdraw.h"
#include "ui_withdraw.h"

withdraw::withdraw(QWidget *parent) : QMainWindow(parent),
                                                    ui(new Ui::withdraw)
{
    ui->setupUi(this);
    ui->label_money->setText(QString::number(this->myUser->showMoney()));
}

withdraw::~withdraw()
{
    delete ui;
}

// push withdraw button
void withdraw::on_pushButton_Withdraw_clicked()
{
    QString money = ui->lineEdit_Withdraw->text();
    switch (this->myUser->getMoney(money.toInt()))
    {
    case getedMoney:
        ui->label_money->setText(QString::number(this->myUser->showMoney()));
        ui->lineEdit_Withdraw->setText("");
        QMessageBox::information(this, "Withdraw", "Your money is back.");
        break;
    case haveDebtAmount:
        QMessageBox::critical(this, "Error", "You are in debt!");
        break;
    case MoreThanInventory:
        QMessageBox::critical(this, "Error", "This amount of money is more than how much you have!");
        break;
    default:
        QMessageBox::warning(this, "?", "?");
    }
}

// push charge button
void withdraw::on_pushButton_Charge_clicked()
{
    QString money = ui->lineEdit_Charge->text();
    this->myUser->chargeAccount(money.toInt());
    ui->label_money->setText(QString::number(this->myUser->showMoney()));
    ui->lineEdit_Charge->setText("");
    QMessageBox::information(this, "Charge", "Your money is charged.");
}

// choose change information
void withdraw::on_actionInformation_triggered()
{
    this->deleteUserClass();
    hide();
    this->ChangeAccount = new chengeAccount(this);
    this->ChangeAccount->show();
}

// choose change password
void withdraw::on_actionPassword_triggered()
{
    this->deleteUserClass();
    hide();
    this->changePassword = new chengPassword(this);
    this->changePassword->show();
}

// choose charge and withdraw money
void withdraw::on_actionCharge_and_withdraw_money_triggered(){}

// choose sign out
void withdraw::on_actionSign_out_triggered()
{
    this->myUser->logout();
    hide();
    this->deleteUserClass();
    this->mainWindow = new MainWindow(this);
    this->mainWindow->show();
}

// choose exit
void withdraw::on_actionExit_triggered()
{
    this->deleteUserClass();
    close();
}

// choose buy, sale and show stocks
void withdraw::on_actionStock_triggered()
{
    this->deleteUserClass();
    hide();
    this->basicWindow = new BasicWindow(this);
    this->basicWindow->show();
}

// delete the User object
void withdraw::deleteUserClass()
{
    delete this->myUser;
    this->myUser = 0;
}
