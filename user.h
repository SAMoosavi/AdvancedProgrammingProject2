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

enum ECheng
{
    EChengeName,
    EChengeID,
    EChengeAccountNumber,
    EChengeIBAN,
    EChengeUsername,
    chenged,
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

    bool withdrawAccount(int money);

    QString userStructToString(user *us);

    user *userLogin = 0;

    const QString pathFile = "C:/Users/moosavi/Desktop/AP/AdvancedProgrammingProject2/rec/user_data.csv";

public:
    User();
    ~User();

    ERegister Register(QString &username, QString &password, QString &confirmPassword);
    ESetAccount setAccount(QString &name, QString &ID, QString &accountNumber, QString &IBAN);
    ELogin login(QString &username, QString &password);

    ECheng chengAccount(QString &username, QString &name, QString &ID, QString &accountNumber, QString &IBAN);
    EChengePassword chengePassword(QString &password, QString &confirmPassword);

    user *getUserLogin();
    bool isLogin();
    void logout();

    bool accountIsSet();

    void chargeAccount(int money);
    EGetMoney getMoney(int money);
    int showMoney();

    bool save(user *us);
    user *read(QString &username);
    bool replace(user *us, QString pUsername = "");
};

#endif // USER_H
