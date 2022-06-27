#include "basewindow.h"
#include "ui_basewindow.h"

BaseWindow::BaseWindow(User *myUser, QWidget *parent) : QMainWindow(parent),
                                                        ui(new Ui::BaseWindow)
{
    ui->setupUi(this);
    this->myUser = myUser;

    /*user *loginUser = myUser->getUserLogin();

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Symbol"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Full Name"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Price"));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem("Value"));

    for(auto st: loginUser->stocks){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(st->symbol));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(st->name));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(st->price));
        //TODO: save amount and use it
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(st->price));
    }
*/
}

BaseWindow::~BaseWindow()
{
    delete ui;
}
