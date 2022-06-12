#include "stock.h"
#include "user.h"

Stock::Stock()
{

}

Stock::~Stock()
{

}

bool Stock::buyStock(QString &username, QString &symbol, int amount)
{
   auto us = User::searchUser(username);
   if(us)
   {
       auto st = searchStock(symbol);
       if(st)
       {
           if(us->dabtMoney >= amount*st->price)
           {
               us->stocks.push_back(st);
               us->dabtMoney -= amount*st->price;
               return true;
           }
       }
   }
   return false;
}

void Stock::saleStock(QString &username, QString &symbol)
{
   auto us = User::searchUser(username);
   if(us)
   {
       auto st = searchStock(symbol);
       if(st)
       {
           us->dabtMoney += st->price;
           us->stocks.erase(find(us->stocks.begin(), us->stocks.end(), st));
       }
   }
}

void Stock::getStocks()
{

}

void Stock::getAllStocks()
{

}

stock *Stock::searchStock(QString &symbol)
{
    for (auto st : stocks)
    {
        if (st->symbol == symbol)
        {
            return st;
        }
    }
    return nullptr;
}
