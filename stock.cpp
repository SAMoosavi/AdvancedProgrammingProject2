#include "stock.h"
#include "user.h"

class User;

struct user;

Stock::Stock()
{

}

Stock::~Stock()
{

}

bool Stock::buyStock(user *us, QString &symbol, int amount)
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
   return false;
}

void Stock::saleStock(user *us, QString &symbol)
{
   auto st = searchStock(symbol);
   if(st)
   {
       us->dabtMoney += st->price;
       us->stocks.erase(find(us->stocks.begin(), us->stocks.end(), st));
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
