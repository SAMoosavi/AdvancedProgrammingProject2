#ifndef STOCK_H
#define STOCK_H
#include <bits/stdc++.h>
#include <QString>
#include "user.h"

class User;
struct user;

using std::map;
using std::pair;
using std::vector;

struct stock
{
    int ID;
    QString symbol;
    QString name;
    double price;
    long long marketCap;
};

enum EBuy
{
    bought,
    fileNotFound,
    notEnoughMoney,
};

class Stock
{
private:
    // const QString pathStockUserFile = "C:/Users/Lenovo/Desktop/AP/AdvancedProgrammingProject2/rec/stock_user_data.csv";
    const QString pathStockUserFile = "C:/Users/Lenovo/Desktop/AdvancedProgrammingProject2/rec/stock_user_data.csv";

    bool saveOnStockUser(int id, int amount);
    bool deleteFromStockUser(int id);

    user *us;

public:
    Stock();
    ~Stock();

    bool readOnStockUser();

    EBuy buyStock(int id, int amount);
    bool saleStock(int id);

    stock *searchStock(user *us, int id);
    map<int, stock *> allStocks;
    bool read();
};

#endif // STOCK_H
