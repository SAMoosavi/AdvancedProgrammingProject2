#ifndef USER_H
#define USER_H
#include <bits/stdc++.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "stock.h"

class Stock;

struct stock;

using std::vector;

struct user
{
    QString username;
    QString password;
    QString name;
    QString ID;
    QString accountNumber;
    //! International Bank Account Number
    QString IBAN;
    int debtAmount = 0;
    int money = 0;
    int stockN;
    vector<stock *> stocks;
};

enum ERegister
{
    registered,
    EVPassword,
    EConfirmPassword,
    notAvailableUsername,
};

enum ELogin
{
    logined,
    notFuond,
    notCorrectPassword,
};

enum ESetAccount
{
    setedAccount,
    EVName,
    EVID,
    EVAccountNumber,
    EVIBAN,
};

enum EChengePassword
{
    chengedPassword,
    eVPassword,
    eConfirmPassword,
};

enum EGetMoney
{
    getedMoney,
    haveDebtAmount,
    MoreThanInventory,
};

class User
{
private:
    vector<user *> users;

    bool vPassword(QString &password);
    bool confirmedPassword(QString &password, QString &confirmPassword);
    QString hashPassword(QString &password);

    bool vName(QString &name);
    bool vID(QString &ID);
    bool vAccountNumber(QString &accountNumber);
    bool vIBAN(QString &IBAN);

    bool vDebtAmount(int debtAmount);

    user *searchUser(QString &username);

    bool withdrawAccount(int money);

    user *userLogin = 0;

    const QString fileName = "C:/Users/moosavi/Desktop/AP/AdvancedProgrammingProject2/rec/user_data.csv";

public:
    User();
    ~User();

    ERegister Register(QString &username, QString &password, QString &confirmPassword);
    ESetAccount setAccount(QString &name, QString &ID, QString &accountNumber, QString &IBAN);
    ELogin login(QString &username, QString &password);

    bool chengeName(QString &name);
    bool chengeID(QString &ID);
    bool chengeAccountNumber(QString &accountNumber);
    bool chengeIBAN(QString &IBAN);
    bool chengeUsername(QString &username);
    EChengePassword chengePassword(QString &password, QString &confirmPassword);

    user *getUserLogin();
    bool isLogin();
    void logout();

    bool accountIsSet();

    void chargeAccount(int money);
    EGetMoney getMoney(int money);

    bool save(user *us);
    bool read();
};

#endif // USER_H
