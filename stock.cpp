#include "stock.h"
#include "user.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

class User;

struct user;

map<int, stock *> Stock::allStocks = {};

using std::map;
using std::vector;

Stock::Stock()
{
    this->read();
}

Stock::~Stock()
{
}

EBuy Stock::buyStock(user *us, int id, int amount)
{

    auto st = searchStock(nullptr, id);
    if (st)
    {
        if (us->money >= amount * st->price)
        {
            if(saveOnStockUser(us, id, amount)){

                us->money -= amount * st->price;
                return bought;
            }
            else{
                return fileNotFound;
            }

        }
        else if(us->money + 1000*1000 - us->debtAmount >= amount * st->price)
        {
            if(saveOnStockUser(us, id, amount)){

                us->debtAmount += amount * st->price - us->money;
                us->money = 0;
                return bought;
            }
            else{
                return fileNotFound;
            }
        }

    }
    return notEnoughMoney;
}


bool Stock::saleStock(user *us, int id)
{

        for(int i = 0; i < us->stocks.size(); i++){
            if(us->stocks[i].first->ID == id){
                us->money += us->stocks[i].first->price;
                us->stocks.erase(us->stocks.begin()+i);
                if(!deleteFromStockUser(us, id)){
                    return false;
                }
            }
        }
        return true;
        //us->stocks.erase(find(us->stocks.begin(), us->stocks.end(), {st}));
}


/*
map<int, stock *> Stock::getStocks(user *us)
{
    map<int, stock *> stocks;
    for (auto st : us->stocks)
    {
        stocks[st->ID] = st;
    }

    return stocks;
}


map<int, stock *> Stock::getAllStocks()
{
    return allStocks;
}
*/

stock *Stock::searchStock(user *us, int id)
{
    if(us == nullptr){
        for (auto st : allStocks)
        {
            if (st.first == id)
            {
                return st.second;
            }
        }
        return nullptr;
    }

    for (auto st : us->stocks)
    {
        if (st.first->ID == id)
        {
            return st.first;
        }
    }
    return nullptr;
}

bool Stock::read()
{
    QFile file("C:/Users/moosavi/Desktop/AP/AdvancedProgrammingProject2/rec/stock_market_data.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    bool ok = false;
    while (!in.atEnd())
    {
        if (!ok)
        {
            ok = true;
            continue;
        }

        QString line = in.readLine();

        int q = 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '"')
                q++;

            if (q % 2 == 1 && line[i] == ',')
            {
                line[i] = '`';
            }
        }

        QStringList list = line.split(",");

        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '`')
                line[i] = ',';
        }

        stock *tStock = new stock;
        tStock->ID = list[0].toInt();
        tStock->symbol = list[1];

        if (list[2][0] == '"')
        {
            list[2][0] = ' ';
            list[2][list.size() - 1] = ' ';
        }

        tStock->name = list[2];
        tStock->price = list[3].toDouble();
        tStock->marketCap = list[4].toLongLong();
        allStocks[tStock->ID] = tStock;
    }
    return true;
}

bool Stock::saveOnStockUser(user *us, int id, int amount)
{

    QString firstline = "", other = "";

    QFile readFile("C:/Users/moosavi/Desktop/AP/AdvancedProgrammingProject2/rec/stock_user_data.csv");
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&readFile);
    bool ok = false;
    int am = amount;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(",");

        if (ok && us->ID == list[0])
        {
            if (list[1].toInt() != id)
            {
                other += line + '\n';
            }
            else{
                am += list[2].toInt();
            }
        }
        else
        {
            firstline += line + '\n';
        }

        if (!ok)
        {
            ok = true;
        }
    }
    QString buy = us->ID + "," + QString::number(id) + "," + QString::number(am);
    QString str = firstline + other + buy + '\n';

    readFile.flush();
    readFile.close();

    QFile writeFile("C:/Users/moosavi/Desktop/AP/AdvancedProgrammingProject2/rec/stock_user_data.csv");
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&writeFile);
    out << str;
    writeFile.flush();
    writeFile.close();

    if(readOnStockUser(us)){
        return true;
    }
    else{
        return false;
    }
}

bool Stock::readOnStockUser(user *us)
{
    us->stocks.clear();
    pair<stock *, int> tPair;

    QFile readFile("C:/Users/moosavi/Desktop/AP/AdvancedProgrammingProject2/rec/stock_user_data.csv");
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&readFile);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(",");

        if (us->ID == list[0])
        {
            tPair.first = searchStock(nullptr, list[1].toInt());
            tPair.second = list[2].toInt();
            us->stocks.push_back(tPair);
        }
    }

    readFile.flush();
    readFile.close();

    return true;
}

bool Stock::deleteFromStockUser(user *us, int id)
{
    QString str;

    QFile readFile("C:/Users/moosavi/Desktop/AP/AdvancedProgrammingProject2/rec/stock_user_data.csv");
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&readFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(",");

        if (us->ID != list[0] || list[1].toInt() != id)
        {
            str += line + '\n';
        }
    }
    readFile.flush();
    readFile.close();

    QFile writeFile("C:/Users/moosavi/Desktop/AP/AdvancedProgrammingProject2/rec/stock_user_data.csv");
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&writeFile);
    out << str;
    writeFile.flush();
    writeFile.close();
    return true;
}

