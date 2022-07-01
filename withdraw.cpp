#include "withdraw.h"
#include "ui_withdraw.h"

withdraw::withdraw(User *myUser, QWidget *parent) : QMainWindow(parent),
                                                    ui(new Ui::withdraw)
{
    ui->setupUi(this);
    this->myUser = myUser;
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
