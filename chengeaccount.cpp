#include "chengeaccount.h"
#include "ui_chengeaccount.h"

chengeAccount::chengeAccount(User *myUser, QWidget *parent) : QMainWindow(parent),
                                                              ui(new Ui::chengeAccount)
{
    ui->setupUi(this);
    this->myUser = myUser;

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
    case chenged:
        QMessageBox::information(this, "Edit Account", "Your account updated.");
        break;
    case EChengeName:
        QMessageBox::critical(this, "Error", "Name must be less than 40 letters!");
        break;
    case EChengeID:
        QMessageBox::critical(this, "Error", "ID must be 10 letters!");
        break;
    case EChengeAccountNumber:
        QMessageBox::critical(this, "Error", "Account number must be 10 letters!");
        break;
    case EChengeIBAN:
        QMessageBox::critical(this, "Error", "IBAN is not correct!");
        break;
    case EChengeUsername:
        QMessageBox::critical(this, "Error", "Your username is not available!");
        break;
    default:
        QMessageBox::warning(this, "?", "?");
    }
}


void chengeAccount::on_actionInformation_triggered()
{
//    hide();
//    this->CengeAccount = new chengeAccount(this->myUser, this);
//    this->CengeAccount->show();
}


void chengeAccount::on_actionPassword_triggered()
{
    hide();
    this->ChengPassword = new chengPassword(this->myUser, this);
    this->ChengPassword->show();
}


void chengeAccount::on_actionCharge_and_triggered()
{
    hide();
    this->Withdraw = new withdraw(this->myUser, this);
    this->Withdraw->show();
}


void chengeAccount::on_actionSing_out_triggered()
{
    this->myUser->logout();
    hide();
    this->mainWindow = new MainWindow(this->myUser, this);
    this->mainWindow->show();
}


void chengeAccount::on_actionExit_triggered()
{
    close();
}


void chengeAccount::on_actionstock_triggered()
{
    hide();
    this->basicWindow = new BasicWindow(this->myUser, this);
    this->basicWindow->show();
}


