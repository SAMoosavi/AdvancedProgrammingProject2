#include "basicwindow.h"
#include "ui_basicwindow.h"

BasicWindow::BasicWindow(User *myUser, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasicWindow)
{
    ui->setupUi(this);

    this->myUser = myUser;

    user *loginUser = myUser->getUserLogin();

    ui->tableView->insertRow(ui->tableView->rowCount());
    ui->tableView->setColumnCount(4);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->setItem(0, 0, new QtableViewItem("Symbol"));
    ui->tableView->setItem(0, 1, new QtableViewItem("Full Name"));
    ui->tableView->setItem(0, 2, new QtableViewItem("Price"));
    ui->tableView->setItem(0, 3, new QtableViewItem("Value"));
/*
    int i = 1;
    for(auto st: loginUser->stocks){
        ui->tableView->insertRow(ui->tableView->rowCount());
        ui->tableView->setItem(i, 0, new QtableViewItem(st->symbol));
        ui->tableView->setItem(i, 1, new QtableViewItem(st->name));
        ui->tableView->setItem(i, 2, new QtableViewItem(st->price));
        TODO: save amount and use it
        ui->tableView->setItem(i, 3, new QtableViewItem(st->price));
        i++;
    }
*/
}

BasicWindow::~BasicWindow()
{
    delete ui;
}
