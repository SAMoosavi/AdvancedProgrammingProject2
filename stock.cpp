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

bool Stock::buyStock(QString &symbol, int amount)
{
   auto st = searchStock(symbol);
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

void Stock::saleStock(QString &symbol)
{
   auto st = searchStock(symbol);
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

stock *Stock::searchStock(QString &symbol)
{
    for (auto st : us->stocks)
    {
        if (st->symbol == symbol)
        {
            return st;
        }
    }
    return nullptr;
}

bool Stock::save()
{
    return false;
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
        QStringList list = line.split(",");
        stock* tStock = new stock;
        tStock->ID = list[0].toInt();
        tStock->symbol = list[1];
        tStock->name = list[2];
        tStock->price = list[3].toDouble();
        tStock->marketCap = list[4].toInt();
        this->allStocks[tStock->ID] = tStock;
    }

    return true;
}
