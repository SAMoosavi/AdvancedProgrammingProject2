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

    this->showAllStocks();

    for(auto st: Stock::allStocks){
        ui->comboBox_buy->addItem(st.second->symbol);
    }


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
    if(Stock::buyStock(us, id, QString(ui->lineEdit_buy->text()).toInt())){

        if(Stock::addToStockUser(us, id, QString(ui->lineEdit_buy->text()).toInt())){
            QMessageBox::information(this, "congratulations!", "Operation was successful");
        }
        else{
            QMessageBox::critical(this, "Error", "File not found");
        }
    }
    else{
        QMessageBox::critical(this, "Error", "Your money is not enough");
    }
}

void BasicWindow::on_pushButton_buy_clicked()
{
    buyStock();
}

