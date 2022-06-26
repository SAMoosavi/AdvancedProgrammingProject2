#include "setaccount.h"
#include "ui_setaccount.h"

SetAccount::SetAccount(User *myUser, QWidget *parent) : QMainWindow(parent),
                                                        ui(new Ui::SetAccount)
{
    ui->setupUi(this);
    this->myUser = myUser;
}

SetAccount::~SetAccount()
{
    delete ui;
}

void SetAccount::on_pushButton_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString ID = ui->lineEdit_ID->text();
    QString accountNumber = ui->lineEdit_account_number->text();
    QString IBAN = ui->lineEdit_IBAN->text();

    switch (this->myUser->setAccount(name, ID, accountNumber, IBAN))
    {
    case setedAccount:
        QMessageBox::information(this, "Welcome!", "Welcome!");
        // TODO: cheng page
        break;
    case EVName:
        QMessageBox::critical(this, "Error", "Name must be less than 40 letters!");
        break;
    case EVID:
        QMessageBox::critical(this, "Error", "ID must be 10 letters!");
        break;
    case EVAccountNumber:
        QMessageBox::critical(this, "Error", "Account number must be 10 letters!");
        break;
    case EVIBAN:
        QMessageBox::critical(this, "Error", "IBAN is not correct!");
        break;
    default:
        QMessageBox::warning(this, "?", "?");
    }
}
