#ifndef STOCK_H
#define STOCK_H
#include <bits/stdc++.h>
#include <QString>

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
    vector<stock*> stocks;
public:
    Stock();
    ~Stock();

    bool buyStock(QString &username, QString &symbol, int amount);
    void saleStock(QString &username, QString &symbol);
    void getStocks();
    void getAllStocks();

    stock *searchStock(QString &symbol);
};

#endif // STOCK_H
