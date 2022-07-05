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
    // create new User object to use it's function
    User *myUser = new User();
    this->us = myUser->getUserLogin();
    this->read();
}

Stock::~Stock()
{
}

EBuy Stock::buyStock(int id, int amount)
{
    // search stock in allstock
    auto st = searchStock(nullptr, id);
    if (st)
    {
        // if money is enough
        if (us->money >= amount * st->price)
        {
            if (saveOnStockUser(id, amount))
            {
                us->money -= amount * st->price;

                // create new User object to use it's function
                User *myUser = new User();
                myUser->replace(us);
                return bought;
            }
            else
            {
                return fileNotFound;
            }
        }

        // if using debt is possible
        else if (us->money + 1000 * 1000 - us->debtAmount >= amount * st->price)
        {
            if (saveOnStockUser(id, amount))
            {

                us->debtAmount += amount * st->price - us->money;
                us->money = 0;

                // create new User object to use it's function
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
    // search stock in us->stocks
    for (int i = 0; i < us->stocks.size(); i++)
    {
        if (us->stocks[i].first->ID == id)
        {
            // if debtamount is more than how much we get
            if(us->debtAmount >= us->stocks[i].first->price * us->stocks[i].second){
                us->debtAmount -= us->stocks[i].first->price * us->stocks[i].second;
            }

            // if debtamount is less than how much we get
            else{
                us->money += us->stocks[i].first->price * us->stocks[i].second - us->debtAmount;
                us->debtAmount = 0;
            }

            // delete stock from us->stocks
            us->stocks.erase(us->stocks.begin() + i);
            if (!deleteFromStockUser(id))
            {
                return false;
            }

            // create new User object to use it's function
            User *myUser = new User();
            myUser->replace(us);
        }
    }
    return true;
}

stock *Stock::searchStock(user *us, int id)
{
    // search stock in allstocks
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

    // search stock in us->stocks
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
    // open file
    QFile file(this->pathStock);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    bool ok = false;

    // read file line by line
    while (!in.atEnd())
    {
        // ignore first line
        if (!ok)
        {
            ok = true;
            continue;
        }

        QString line = in.readLine();

        // check if name has "," in it and changed "," to "`"
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

        // change "`" to ","
        for (int i = 0; i < list[2].size(); i++)
        {
            if (list[2][i] == '`')
                list[2][i] = ',';
        }

        // create new stock to add to allstocks
        stock *tStock = new stock;
        tStock->ID = list[0].toInt();
        tStock->symbol = list[1];

        // change " to space
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

    // close file
    file.flush();
    file.close();
    return true;
}

bool Stock::saveOnStockUser(int id, int amount)
{

    QString firstline = "", other = "";

    // open file
    QFile readFile(this->pathStockUserFile);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&readFile);
    bool ok = false;
    int am = amount;

    // read file line by line
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(",");

        // add amount to am
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

    // close file
    readFile.flush();
    readFile.close();

    // write on file
    QFile writeFile(this->pathStockUserFile);
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&writeFile);
    out << str;

    // close file
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
    // clean us->stocks
    us->stocks.clear();

    // creat new pair to add to us->stocks
    pair<stock *, int> tPair;

    // open file
    QFile readFile(this->pathStockUserFile);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&readFile);

    // read file line by line
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

    // close file
    readFile.flush();
    readFile.close();

    return true;
}

bool Stock::deleteFromStockUser(int id)
{
    QString str;

    // open file
    QFile readFile(this->pathStockUserFile);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&readFile);

    // read file line by line
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(",");

        // ignore user with that id
        if (us->ID != list[0] || list[1].toInt() != id)
        {
            str += line + '\n';
        }
    }

    // close file
    readFile.flush();
    readFile.close();

    QFile writeFile(this->pathStockUserFile);
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&writeFile);

    // write on file
    out << str;

    // close file
    writeFile.flush();
    writeFile.close();
    return true;
}
