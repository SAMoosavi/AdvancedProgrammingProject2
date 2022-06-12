#ifndef USER_H
#define USER_H
#include <bits/stdc++.h>
#include <QString>
#include "stock.h"

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
    int dabtMoney = 0;
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
    static vector<user *> users;

    bool vPassword(QString &password);
    bool confirmedPassword(QString &password, QString &confirmPassword);
    QString hashPassword(QString &password);

    bool vName(QString &name);
    bool vID(QString &ID);
    bool vAccountNumber(QString &accountNumber);
    bool vIBAN(QString &IBAN);

    bool vDebtAmount(int debtAmount);

    

    bool withdrawAccount(int money);

    user *userLogin = 0;

public:
    User();
    ~User();
    
    static user *searchUser(QString &username);
    
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

    void chargeAccount(int money);
    EGetMoney getMoney(int money);

    //void buyStock(QString &symbol, int amount);
    //void saleStock(QString &symbol);

    // vector<stock *> getStock();

    bool save();
    bool read();

};

#endif // USER_H
