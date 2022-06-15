#include "setaccount.h"
#include "ui_setaccount.h"

SetAccount::SetAccount(User *myUser,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetAccount)
{
    ui->setupUi(this);
    this->myUser = myUser;
}

SetAccount::~SetAccount()
{
    delete ui;
}
