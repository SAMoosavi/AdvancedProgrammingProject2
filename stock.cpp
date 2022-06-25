#include "stock.h"
#include "user.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>


class User;

struct user;

using std::vector;
using std::map;

Stock::Stock(user *userr)
{
    this->us = userr;

    this->read();
}

Stock::~Stock()
{

}

bool Stock::buyStock(int id, int amount)
{
   auto st = searchStock(id);
   if(st)
   {
       if(this->us->money >= amount*st->price)
       {
           this->us->stocks.push_back(st);
           this->us->money -= amount*st->price;
           return true;
       }
   }
   return false;
}

void Stock::saleStock(int id)
{
   auto st = searchStock(id);
   if(st)
   {
       this->us->money += st->price;
       this->us->stocks.erase(find(us->stocks.begin(), us->stocks.end(), st));
   }
}

map<int, stock*> Stock::getStocks()
{
    map<int, stock*> stocks;
    for(auto st: this->us->stocks)
    {
        stocks[st->ID] = st;
    }

    return stocks;
}

map<int, stock*> Stock::getAllStocks()
{
    return allStocks;
}

stock *Stock::searchStock(int id)
{
    for (auto st : us->stocks)
    {
        if (st->ID == id)
        {
            return st;
        }
    }
    return nullptr;
}

bool Stock::read()
{
    QFile file(":/rec/stock_market_data.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    bool ok = false;
    while (!in.atEnd()) {
        if(!ok){
            ok = true;
            continue;
        }

        QString line = in.readLine();

        int q = 0;
        for(int i = 0; i < line.size(); i++){
            if(line[i] == '"') q++;

            if(q%2 == 1 && line[i] == ','){
                line[i] = '`';
            }
        }

        QStringList list = line.split(",");

        for(int i = 0; i < line.size(); i++){
            if(line[i] == '`') line[i] = ',';
        }

        stock* tStock = new stock;
        tStock->ID = list[0].toInt();
        tStock->symbol = list[1];

        if(list[2][0] == '"'){
            list[2][0] = ' ';
            list[2][list.size()-1] = ' ';
        }
        tStock->name = list[2];
        tStock->price = list[3].toDouble();
        tStock->marketCap = list[4].toInt();
        this->allStocks[tStock->ID] = tStock;
    }

    return true;
}

bool Stock::saveOnStockUser(int id , int amount){

    QString str = "" , user = "",other = "";

    QFile readFile(this->pathStockUserFile);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&readFile);
    bool ok = false;
    QString bay = amount == 0 ? "" :this->us->ID + ","+ QString::number(id) + "," + QString::number(amount);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(",");

        if (ok && this->us->ID == list[0])
        {
            if(list[1].toInt() != id){
                user += line;
            }
        }
        else
        {
            other += line;
        }

        if (!ok)
        {
            ok = true;
        }
    }
    str = user + bay + other;

    readFile.flush();
    readFile.close();

    QFile writeFile(this->pathStockUserFile);
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&writeFile);
    out << str;
    writeFile.flush();
    writeFile.close();

    return true;
}

vector<pair<stock*,int > > Stock::readOnStockUser(){
    vector<pair<stock*,int > > result;
    pair<stock*,int > tPair;
    QString userId  = this->us->ID;

    QFile readFile(this->pathStockUserFile);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return result;

    QTextStream in(&readFile);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(",");

        if (userId == list[0])
        {
           tPair.first = this->searchStock(list[1]);
           tPair.second = list[2].toInt();
           result.push_back(tPair);
        }
    }

    readFile.flush();
    readFile.close();

    return result;
}
