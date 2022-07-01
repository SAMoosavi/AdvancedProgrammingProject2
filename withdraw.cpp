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

void withdraw::on_pushButton_Withdraw_clicked()
{
    QString money = ui->lineEdit_Withdraw->text();
    switch (this->myUser->getMoney(money.toInt()))
    {
    case getedMoney:
        ui->label_money->setText(QString::number(this->myUser->showMoney()));
        ui->lineEdit_Withdraw->setText("");
        QMessageBox::information(this, "Withdraw", "Withdrawed money.");
        break;
    case haveDebtAmount:
        QMessageBox::critical(this, "Error", "You have debt amunt!");
        break;
    case MoreThanInventory:
        QMessageBox::critical(this, "Error", "Your money is more than inventory!");
        break;
    default:
        QMessageBox::warning(this, "?", "?");
    }
}

void withdraw::on_pushButton_Charge_clicked()
{
    QString money = ui->lineEdit_Charge->text();
    this->myUser->chargeAccount(money.toInt());
    ui->label_money->setText(QString::number(this->myUser->showMoney()));
    ui->lineEdit_Charge->setText("");
    QMessageBox::information(this, "Charge", "Charged money.");
}

void withdraw::on_actionInformation_triggered()
{
    this->deleteUserClass();
    hide();
    this->ChangeAccount = new chengeAccount(this);
    this->ChangeAccount->show();
}

void withdraw::on_actionPassword_triggered()
{
    this->deleteUserClass();
    hide();
    this->changePassword = new chengPassword(this);
    this->changePassword->show();
}

void withdraw::on_actionCharge_and_withdraw_money_triggered(){}

void withdraw::on_actionSign_out_triggered()
{
    this->myUser->logout();
    hide();
    this->deleteUserClass();
    this->mainWindow = new MainWindow(this);
    this->mainWindow->show();
}

void withdraw::on_actionExit_triggered()
{
    this->deleteUserClass();
    close();
}

void withdraw::deleteUserClass()
{
    delete this->myUser;
    this->myUser = 0;
}

void withdraw::on_actionStock_triggered()
{
    this->deleteUserClass();
    hide();
    this->basicWindow = new BasicWindow(this);
    this->basicWindow->show();
}
