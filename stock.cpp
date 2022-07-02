#include "stock.h"
#include "user.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

class User;

struct user;

using std::map;
using std::vector;

Stock::Stock()
{
    User *myUser = new User();
    this->us = myUser->getUserLogin();
    this->read();
}

Stock::~Stock()
{
}

EBuy Stock::buyStock(int id, int amount)
{

    auto st = searchStock(nullptr, id);
    if (st)
    {

        if (us->money >= amount * st->price)
        {
            if (saveOnStockUser(id, amount))
            {

                us->money -= amount * st->price;
                User *myUser = new User();
                myUser->replace(us);
                return bought;
            }
            else
            {
                return fileNotFound;
            }
        }
        else if (us->money + 1000 * 1000 - us->debtAmount >= amount * st->price)
        {
            if (saveOnStockUser(id, amount))
            {

                us->debtAmount += amount * st->price - us->money;
                us->money = 0;
                User *myUser = new User();
                myUser->replace(us);
                return bought;
            }
            else
            {
                return fileNotFound;
            }
        }
    }
    return notEnoughMoney;
}

bool Stock::saleStock(int id)
{

    for (int i = 0; i < us->stocks.size(); i++)
    {
        if (us->stocks[i].first->ID == id)
        {
            us->money += us->stocks[i].first->price * us->stocks[i].second;
            us->stocks.erase(us->stocks.begin() + i);
            if (!deleteFromStockUser(id))
            {
                return false;
            }
        }
    }
    return true;
}

stock *Stock::searchStock(user *us, int id)
{
    if (us == nullptr)
    {
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
    QFile file(this->pathStock);

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

        for (int i = 0; i < list[2].size(); i++)
        {
            if (list[2][i] == '`')
                list[2][i] = ',';
        }

        stock *tStock = new stock;
        tStock->ID = list[0].toInt();
        tStock->symbol = list[1];

        if (list[2][0] == '"')
        {
            list[2][0] = ' ';
            list[2][list[2].size() - 1] = ' ';
        }

        tStock->name = list[2];
        tStock->price = list[3].toDouble();
        tStock->marketCap = list[4].toLongLong();
        allStocks[tStock->ID] = tStock;
    }
    return true;
}

bool Stock::saveOnStockUser(int id, int amount)
{

    QString firstline = "", other = "";

    QFile readFile(this->pathStockUserFile);
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
            else
            {
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

    QFile writeFile(this->pathStockUserFile);
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&writeFile);
    out << str;
    writeFile.flush();
    writeFile.close();

    if (readOnStockUser())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Stock::readOnStockUser()
{
    us->stocks.clear();
    pair<stock *, int> tPair;

    QFile readFile(this->pathStockUserFile);
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

bool Stock::deleteFromStockUser(int id)
{
    QString str;

    QFile readFile(this->pathStockUserFile);
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

    QFile writeFile(this->pathStockUserFile);
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&writeFile);
    out << str;
    writeFile.flush();
    writeFile.close();
    return true;
}
