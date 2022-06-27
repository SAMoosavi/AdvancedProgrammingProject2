#include "basicwindow.h"
#include "ui_basicwindow.h"

BasicWindow::BasicWindow(User *myUser, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasicWindow)
{
    ui->setupUi(this);

    this->myUser = myUser;

    user *loginUser = myUser->getUserLogin();

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Symbol"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Full Name"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Price"));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem("Value"));
/*
    int i = 1;
    for(auto st: loginUser->stocks){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(st->symbol));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(st->name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(st->price));
        TODO: save amount and use it
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(st->price));
        i++;
    }
*/
}

BasicWindow::~BasicWindow()
{
    delete ui;
}
