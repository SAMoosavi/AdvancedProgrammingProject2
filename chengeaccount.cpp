#include "chengeaccount.h"
#include "ui_chengeaccount.h"

chengeAccount::chengeAccount( QWidget *parent) : QMainWindow(parent),
                                                              ui(new Ui::chengeAccount)
{
    ui->setupUi(this);
    user *loginUser = myUser->getUserLogin();
    ui->lineEdit_username->setText(loginUser->username);
    ui->lineEdit_IBAN->setText(loginUser->IBAN);
    ui->lineEdit_ID->setText(loginUser->ID);
    ui->lineEdit_name->setText(loginUser->name);
    ui->lineEdit_account_number->setText(loginUser->accountNumber);
}

chengeAccount::~chengeAccount()
{
    delete ui;
}

void chengeAccount::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString name = ui->lineEdit_name->text();
    QString ID = ui->lineEdit_ID->text();
    QString accountNumber = ui->lineEdit_account_number->text();
    QString IBAN = ui->lineEdit_IBAN->text();

    switch (this->myUser->changeAccount(username, name, ID, accountNumber, IBAN))
    {
    case changed:
        QMessageBox::information(this, "Edit Account", "Your account updated.");
        break;
    case EchangeName:
        QMessageBox::critical(this, "Error", "Name must be less than 40 letters!");
        break;
    case EchangeID:
        QMessageBox::critical(this, "Error", "ID must be 10 letters!");
        break;
    case EchangeAccountNumber:
        QMessageBox::critical(this, "Error", "Account number must be 10 letters!");
        break;
    case EchangeIBAN:
        QMessageBox::critical(this, "Error", "IBAN is not correct!");
        break;
    case EchangeUsername:
        QMessageBox::critical(this, "Error", "Your username is not available!");
        break;
    default:
        QMessageBox::warning(this, "?", "?");
    }
}


void chengeAccount::on_actionInformation_triggered(){}


void chengeAccount::on_actionPassword_triggered()
{
    this->deleteUserClass();
    hide();
    this->changePassword = new chengPassword(this);
    this->changePassword->show();
}


void chengeAccount::on_actionCharge_and_triggered()
{
    this->deleteUserClass();
    hide();
    this->Withdraw = new withdraw(this);
    this->Withdraw->show();
}


void chengeAccount::on_actionSing_out_triggered()
{
    this->myUser->logout();
    this->deleteUserClass();
    hide();
    this->mainWindow = new MainWindow(this);
    this->mainWindow->show();
}


void chengeAccount::on_actionExit_triggered()
{
    this->deleteUserClass();
    close();
}

void chengeAccount::deleteUserClass()
{
    delete this->myUser;
    this->myUser = 0;
}


void chengeAccount::on_actionstock_triggered()
{
    this->deleteUserClass();
    hide();
    this->basicWindow = new BasicWindow(this);
    this->basicWindow->show();
}


