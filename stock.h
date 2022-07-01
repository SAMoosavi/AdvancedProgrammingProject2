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

    static bool saveOnStockUser(user *us, int id, int amount);
    static bool readOnStockUser(user *us);
    static bool deleteFromStockUser(user *us, int id);

public:
    Stock();
    ~Stock();

    static EBuy buyStock(user *us, int id, int amount);
    static bool saleStock(user *us, int id);
    map<int, stock *> getStocks(user *us);
    map<int, stock *> getAllStocks();

    static stock *searchStock(user *us, int id);
    static map<int, stock *> allStocks;
    static bool read();
};

#endif // STOCK_H
