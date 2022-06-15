#include "stock.h"
#include "user.h"

class User;

struct user;

using std::vector;

Stock::Stock(user *userr)
{
    this->us = userr;
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

vector<stock*> Stock::getStocks()
{
    vector<stock*> stocks;
    for(auto st: this->us->stocks)
    {
        stocks.push_back(st);
    }

    return stocks;
}

vector<stock*> Stock::getAllStocks()
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
