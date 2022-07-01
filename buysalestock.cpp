#include "buysalestock.h"
#include "ui_buysalestock.h"

buySaleStock::buySaleStock(User *myUser, QWidget *parent) : QMainWindow(parent),
                                                            ui(new Ui::buySaleStock)
{
    ui->setupUi(this);
    this->myUser = myUser;
}

buySaleStock::~buySaleStock()
{
    delete ui;
}
