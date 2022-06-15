#include "setaccount.h"
#include "ui_setaccount.h"

SetAccount::SetAccount(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetAccount)
{
    ui->setupUi(this);
}

SetAccount::~SetAccount()
{
    delete ui;
}
