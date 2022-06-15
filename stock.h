#ifndef STOCK_H
#define STOCK_H
#include <bits/stdc++.h>
#include <QString>
#include "user.h"

class User;
struct user;

using std::vector;

struct stock{
    QString symbol;
    QString name;
    int price;
    int marketCap;
};

class Stock
{
private:
    vector<stock*> allStocks;
    user *us;
public:
    Stock(user *userr);
    ~Stock();

    bool buyStock( QString &symbol, int amount);
    void saleStock(QString &symbol);
    vector<stock*> getStocks();
    vector<stock*> getAllStocks();

    stock *searchStock(QString &symbol);
};

#endif // STOCK_H
