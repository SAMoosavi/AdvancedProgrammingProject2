#include "basicwindow.h"
#include "ui_basicwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "stock.h"

BasicWindow::BasicWindow(User *myUser, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasicWindow)
{
    ui->setupUi(this);
    this->myUser = myUser;
    user *us = myUser->getUserLogin();

    this->showAllStocks();
    this->showStocks(us);
    for(auto st: Stock::allStocks){
        ui->comboBox_buy->addItem(st.second->symbol);
    }
    ui->label_money->setText(QString::number(us->money-us->debtAmount));

}

BasicWindow::~BasicWindow()
{
    delete ui;
}

void BasicWindow::showAllStocks()
{
    Stock::read();

    ui->tableWidget_buy->insertRow(ui->tableWidget_buy->rowCount());
    ui->tableWidget_buy->setColumnCount(4);
    ui->tableWidget_buy->verticalHeader()->setVisible(false);
    ui->tableWidget_buy->horizontalHeader()->setVisible(false);
    ui->tableWidget_buy->setItem(0, 0, new QTableWidgetItem("Symbol"));
    ui->tableWidget_buy->setItem(0, 1, new QTableWidgetItem("Full Name"));
    ui->tableWidget_buy->setItem(0, 2, new QTableWidgetItem("Price"));
    ui->tableWidget_buy->setItem(0, 3, new QTableWidgetItem("Market Capacity"));
    for(auto st: Stock::allStocks){
        ui->tableWidget_buy->insertRow(ui->tableWidget_buy->rowCount());
        ui->tableWidget_buy->setItem(st.first+1, 0, new QTableWidgetItem(st.second->symbol));
        ui->tableWidget_buy->setItem(st.first+1, 1, new QTableWidgetItem(st.second->name));
        ui->tableWidget_buy->setItem(st.first+1, 2, new QTableWidgetItem(QString::number(st.second->price)));
        ui->tableWidget_buy->setItem(st.first+1, 3, new QTableWidgetItem(QString::number(st.second->marketCap)));
    }
}

void BasicWindow::showStocks(user *us)
{
    ui->tableWidget_sale->clear();
    ui->tableWidget_sale->setRowCount(0);
    ui->tableWidget_sale->insertRow(ui->tableWidget_sale->rowCount());
    ui->tableWidget_sale->setColumnCount(4);
    ui->tableWidget_sale->verticalHeader()->setVisible(false);
    ui->tableWidget_sale->horizontalHeader()->setVisible(false);
    ui->tableWidget_sale->setItem(0, 0, new QTableWidgetItem("Symbol"));
    ui->tableWidget_sale->setItem(0, 1, new QTableWidgetItem("Full Name"));
    ui->tableWidget_sale->setItem(0, 2, new QTableWidgetItem("Price"));
    ui->tableWidget_sale->setItem(0, 3, new QTableWidgetItem("Value"));

    for(auto st: us->stocks){
        ui->tableWidget_sale->insertRow(ui->tableWidget_sale->rowCount());
        ui->tableWidget_sale->setItem(ui->tableWidget_sale->rowCount()-1, 0, new QTableWidgetItem(st.first->symbol));
        ui->tableWidget_sale->setItem(ui->tableWidget_sale->rowCount()-1, 1, new QTableWidgetItem(st.first->name));
        ui->tableWidget_sale->setItem(ui->tableWidget_sale->rowCount()-1, 2, new QTableWidgetItem(QString::number(st.first->price)));
        ui->tableWidget_sale->setItem(ui->tableWidget_sale->rowCount()-1, 3, new QTableWidgetItem(QString::number(st.first->price * st.second)));
    }
}

void BasicWindow::buyStock()
{
    int id = 0;
    for(auto st: Stock::allStocks){
        if(st.second->symbol == ui->comboBox_buy->currentText()){
            id = st.first;
            break;
        }
    }

    user *us = this->myUser->getUserLogin();
    switch(Stock::buyStock(us, id, QString(ui->lineEdit_buy->text()).toInt())){
    case bought:
        QMessageBox::information(this, "congratulations!", "Operation was successful");
        showStocks(us);
        break;

    case fileNotFound:
        QMessageBox::critical(this, "Error", "File not found!");
        break;
    case notEnoughMoney:
        QMessageBox::critical(this, "Error", "Your money is not enough!");
        break;
    }
    ui->label_money->setText(QString::number(us->money-us->debtAmount));
}

void BasicWindow::on_pushButton_buy_clicked()
{
    buyStock();
}


void BasicWindow::on_actionInformation_triggered()
{
    hide();
    this->CengeAccount = new chengeAccount(this->myUser, this);
    this->CengeAccount->show();
}


void BasicWindow::on_actionPassword_triggered()
{
    hide();
    this->ChengPassword = new chengPassword(this->myUser, this);
    this->ChengPassword->show();
}


void BasicWindow::on_actionCharge_and_withdraw_money_triggered()
{
    hide();
    this->Withdraw = new withdraw(this->myUser, this);
    this->Withdraw->show();
}


void BasicWindow::on_actionSign_out_triggered()
{
    this->myUser->logout();
    hide();
    this->mainWindow = new MainWindow(this->myUser, this);
    this->mainWindow->show();
}

