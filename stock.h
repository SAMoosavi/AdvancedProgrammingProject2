#ifndef STOCK_H
#define STOCK_H
#include <bits/stdc++.h>
#include <QString>
#include "user.h"

class User;
struct user;

using std::vector;
using std::map;

struct stock{
    int ID;
    QString symbol;
    QString name;
    double price;
    int marketCap;
};

class Stock
{
private:
    map<int, stock*> allStocks;
    user *us;
public:
    Stock(user *userr);
    ~Stock();

    bool buyStock(int id, int amount);
    void saleStock(int id);
    map<int, stock*> getStocks();
    map<int, stock*> getAllStocks();

    stock *searchStock(int id);

    bool read();
};

#endif // STOCK_H
