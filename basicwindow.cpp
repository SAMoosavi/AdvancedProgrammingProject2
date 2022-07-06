#include "basicwindow.h"
#include "ui_basicwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "stock.h"

BasicWindow::BasicWindow( QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasicWindow)
{
    ui->setupUi(this);

    // set us
    this->us = myUser->getUserLogin();

    // show all stocks in tabelwidget
    this->showAllStocks();

    // read file and show stocks in tablewidget
    stock->readOnStockUser();
    this->showStocks();

    // fill combobox
    for(auto st: stock->allStocks){
        ui->comboBox_buy->addItem(st.second->symbol);
    }
    for(auto st: us->stocks){
        ui->comboBox_sale->addItem(st.first->symbol);
    }

    // show money
    ui->label_money->setText(QString::number(this->myUser->showMoney()));

}

BasicWindow::~BasicWindow()
{
    delete ui;
}

// show all stocks in tablewidget
void BasicWindow::showAllStocks()
{
    stock->read();

    ui->tableWidget_buy->insertRow(ui->tableWidget_buy->rowCount()); // add row
    ui->tableWidget_buy->setColumnCount(4); // fix column count
    ui->tableWidget_buy->verticalHeader()->setVisible(false); // not show numbers
    ui->tableWidget_buy->horizontalHeader()->setVisible(false); // not show numbers
    ui->tableWidget_buy->setItem(0, 0, new QTableWidgetItem("Symbol"));
    ui->tableWidget_buy->setItem(0, 1, new QTableWidgetItem("Full Name"));
    ui->tableWidget_buy->setItem(0, 2, new QTableWidgetItem("Price"));
    ui->tableWidget_buy->setItem(0, 3, new QTableWidgetItem("Market Capacity"));

    for(auto st: stock->allStocks){
        ui->tableWidget_buy->insertRow(ui->tableWidget_buy->rowCount()); // add row
        ui->tableWidget_buy->setItem(st.first+1, 0, new QTableWidgetItem(st.second->symbol));
        ui->tableWidget_buy->setItem(st.first+1, 1, new QTableWidgetItem(st.second->name));
        ui->tableWidget_buy->setItem(st.first+1, 2, new QTableWidgetItem(QString::number(st.second->price)));
        ui->tableWidget_buy->setItem(st.first+1, 3, new QTableWidgetItem(QString::number(st.second->marketCap)));
    }

    // make items not editable
    ui->tableWidget_buy->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* header = ui->tableWidget_buy->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    // fit items
    header->setStretchLastSection(true);
}

void BasicWindow::showStocks()
{
    ui->tableWidget_sale->clear(); // clear the tablewidget
    ui->tableWidget_sale->setRowCount(0);
    ui->tableWidget_sale->insertRow(ui->tableWidget_sale->rowCount());  // add row
    ui->tableWidget_sale->setColumnCount(4); // fix column count
    ui->tableWidget_sale->verticalHeader()->setVisible(false); // not show numbers
    ui->tableWidget_sale->horizontalHeader()->setVisible(false); // not show numbers
    ui->tableWidget_sale->setItem(0, 0, new QTableWidgetItem("Symbol"));
    ui->tableWidget_sale->setItem(0, 1, new QTableWidgetItem("Full Name"));
    ui->tableWidget_sale->setItem(0, 2, new QTableWidgetItem("Price"));
    ui->tableWidget_sale->setItem(0, 3, new QTableWidgetItem("Value"));

    for(auto st: us->stocks){
        ui->tableWidget_sale->insertRow(ui->tableWidget_sale->rowCount()); // add row
        ui->tableWidget_sale->setItem(ui->tableWidget_sale->rowCount()-1, 0, new QTableWidgetItem(st.first->symbol));
        ui->tableWidget_sale->setItem(ui->tableWidget_sale->rowCount()-1, 1, new QTableWidgetItem(st.first->name));
        ui->tableWidget_sale->setItem(ui->tableWidget_sale->rowCount()-1, 2, new QTableWidgetItem(QString::number(st.first->price)));
        ui->tableWidget_sale->setItem(ui->tableWidget_sale->rowCount()-1, 3, new QTableWidgetItem(QString::number(st.first->price * st.second)));
    }

    // make items not editable
    ui->tableWidget_sale->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* header = ui->tableWidget_sale->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    // fit items
    header->setStretchLastSection(true);
}

// buy a stock
void BasicWindow::buyStock()
{
    // find the stock's id
    int id = 0;
    for(auto st: stock->allStocks){
        if(st.second->symbol == ui->comboBox_buy->currentText()){
            id = st.first;
            break;
        }
    }


    if(ui->lineEdit_buy->text().toInt() != 0){
        switch(stock->buyStock(id, QString(ui->lineEdit_buy->text()).toInt())){ // use buyStock function in Stock class
        case bought:
            QMessageBox::information(this, "congratulations!", "Operation was successful");
            showStocks();
            ui->comboBox_sale->clear();
            for(auto st: us->stocks){
                ui->comboBox_sale->addItem(st.first->symbol);
            }
            break;

        case fileNotFound:
            QMessageBox::critical(this, "Error", "File not found!");
            break;
        case notEnoughMoney:
            QMessageBox::critical(this, "Error", "Your money is not enough!");
            break;
        }
        ui->label_money->setText(QString::number(this->myUser->showMoney()));
    }
}

// sale a stock
void BasicWindow::saleStock()
{
    // find the stock's id
    int id = 0;
    for(auto st: stock->allStocks){
        if(st.second->symbol == ui->comboBox_sale->currentText()){
            id = st.first;
            break;
        }
    }

    if(!stock->saleStock(id)){ // use saleStock function in Stock class
        QMessageBox::critical(this, "Error", "File not found");
    }
    else{

        // fill combobox again
        ui->comboBox_sale->clear();
        for(auto st: us->stocks){
            ui->comboBox_sale->addItem(st.first->symbol);
        }

        // show stocks in tablewidget
        showStocks();

        // show money
        ui->label_money->setText(QString::number(this->myUser->showMoney()));
    }

}

// push buy button
void BasicWindow::on_pushButton_buy_clicked()
{
    buyStock();
}

// push sale button
void BasicWindow::on_pushButton_sale_clicked()
{
    saleStock();
}

// choose change information
void BasicWindow::on_actionInformation_triggered()
{
    this->deleteUserClass();
    hide();
    this->CengeAccount = new chengeAccount(this);
    this->CengeAccount->show();
}

// choose change password
void BasicWindow::on_actionPassword_triggered()
{
    this->deleteUserClass();
    hide();
    this->changePassword = new chengPassword(this);
    this->changePassword->show();
}

// choose charge and withdraw money
void BasicWindow::on_actionCharge_and_withdraw_money_triggered()
{
    this->deleteUserClass();
    hide();
    this->Withdraw = new withdraw(this);
    this->Withdraw->show();
}

// choose sign out
void BasicWindow::on_actionSign_out_triggered()
{
    this->myUser->logout();
    this->deleteUserClass();
    hide();
    this->mainWindow = new MainWindow(this);
    this->mainWindow->show();
}

// choose exit
void BasicWindow::on_actionExit_triggered()
{
    this->deleteUserClass();
    close();
}

// choose buy, sale and show stocks
void BasicWindow::on_actionStock_triggered(){}

// delete the User object
void BasicWindow::deleteUserClass(){
    delete this->myUser;
    this->myUser = 0;
}
