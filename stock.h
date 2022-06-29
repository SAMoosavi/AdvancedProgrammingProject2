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
    int marketCap;
};

class Stock
{
private:
    //map<int, stock *> allStocks;
    user *us;
    const QString pathStockUserFile = "C:/Users/Lenovo/Desktop/AP/AdvancedProgrammingProject2/rec/stock_user_data.csv";
    bool saveOnStockUser(int id, int amount);
    vector<pair<stock *, int>> readOnStockUser();

public:
    Stock(user *userr);
    ~Stock();

    bool buyStock(int id, int amount);
    void saleStock(int id);
    map<int, stock *> getStocks();
    map<int, stock *> getAllStocks();

    stock *searchStock(int id);
    static map<int, stock *> allStocks;
    static bool read();
};

#endif // STOCK_H
