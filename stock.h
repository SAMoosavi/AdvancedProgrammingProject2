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

class Stock
{
private:
    //const QString pathStockUserFile = "C:/Users/Lenovo/Desktop/AP/AdvancedProgrammingProject2/rec/stock_user_data.csv";
    //static bool saveOnStockUser(user *us, int id, int amount);
    //vector<pair<stock *, int>> readOnStockUser(user *us);


public:
    Stock();
    ~Stock();

    static bool buyStock(user *us, int id, int amount);
    static void saleStock(user *us, int id);
    map<int, stock *> getStocks(user *us);
    map<int, stock *> getAllStocks();

    static bool addToStockUser(user *us, int id, int amount);
    static stock *searchStock(user *us, int id);
    static map<int, stock *> allStocks;
    static bool read();
};

#endif // STOCK_H
