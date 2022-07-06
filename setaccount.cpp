#include "setaccount.h"
#include "ui_setaccount.h"

SetAccount::SetAccount(QWidget *parent) : QMainWindow(parent),
                                                        ui(new Ui::SetAccount)
{
    ui->setupUi(this);
}

SetAccount::~SetAccount()
{
    delete ui;
}

// push complete button
void SetAccount::on_pushButton_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString ID = ui->lineEdit_ID->text();
    QString accountNumber = ui->lineEdit_account_number->text();
    QString IBAN = ui->lineEdit_IBAN->text();

    // use setAccount function in User class
    switch (this->myUser->setAccount(name, ID, accountNumber, IBAN))
    {
    case setedAccount:
        QMessageBox::information(this, "Welcome!", "Welcome!");
        this->deleteUserClass();
        hide();
        this->basicWindow = new BasicWindow(this);
        this->basicWindow->show();
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

// delete the User object
void SetAccount::deleteUserClass()
{
    delete this->myUser;
    this->myUser = 0;
}
