#include "user.h"
using namespace std;
#include <QDebug>

User::User()
{
}
User::~User() {}

bool User::vPassword(QString &password)
{
    // Check password have uper and lower case number spesial character and minimome 8 leter
    /*
     *  string a = password.toStdString();
     *  const regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*(\\W|_))(?=^\\S*$).{8,}$");
     *  return regex_match(a, pattern);
     */
    return true;
}

bool User::confirmedPassword(QString &password, QString &confirmPassword)
{
    return password == confirmPassword;
}

QString User::hashPassword(QString &password)
{
    string a = password.toStdString();
    QString b = "";
    for (auto pass : a)
    {
        b += QChar(((pass + 33) % 65) ^ 'A');
    }
    return b;
}

bool User::vName(QString &name)
{
    // maximome 40 character
    return name.length() <= 40;
}

bool User::vID(QString &ID)
{
    // 10 character
    return ID.length() == 10;
}

bool User::vAccountNumber(QString &accountNumber)
{
    // 10 character
    return accountNumber.length() == 10;
}

bool User::vIBAN(QString &IBAN)
{
    // check IR in first and 12 character
    return IBAN[0] == 'I' && IBAN[1] == 'R' && IBAN.length() == 12;
}

bool User::vDebtAmount(int debtAmount)
{
    // check debtAmount maximome 1,000,000
    return debtAmount <= 10e6;
}

ERegister User::Register(QString &username, QString &password, QString &confirmPassword)
{
    // validation
    if (this->read(username))
    {
        return notAvailableUsername;
    }
    if (!this->vPassword(password))
    {
        return EVPassword;
    }
    if (!this->confirmedPassword(password, confirmPassword))
    {
        return EConfirmPassword;
    }
    // validated now create user
    user *us = new user;
    us->username = username;
    us->password = this->hashPassword(password);
    this->save(us);
    return registered;
}

ELogin User::login(QString &username, QString &password)
{
    // search user
    user *us = this->read(username);
    if (!us)
    {
        return notFuond;
    }
    // check password
    if (this->hashPassword(password) != us->password)
    {
        return notCorrectPassword;
    }
    // login user
    this->userLogin = us;
    return logined;
}

ESetAccount User::setAccount(QString &name, QString &ID, QString &accountNumber, QString &IBAN)
{
    // validation
    if (!this->vName(name))
    {
        return EVName;
    }
    if (!this->vID(ID))
    {
        return EVID;
    }
    if (!this->vAccountNumber(accountNumber))
    {
        return EVAccountNumber;
    }
    if (!this->vIBAN(IBAN))
    {
        return EVIBAN;
    }
    // validated now set user
    this->userLogin->name = name;
    this->userLogin->ID = ID;
    this->userLogin->accountNumber = accountNumber;
    this->userLogin->IBAN = IBAN;

    this->replace(this->userLogin);

    return setedAccount;
}

Echange User::changeAccount(QString &username, QString &name, QString &ID, QString &accountNumber, QString &IBAN)
{
    // validation
    if (!this->vName(name))
    {
        return EchangeName;
    }
    if (!this->vID(ID))
    {
        return EchangeID;
    }
    if (!this->vAccountNumber(accountNumber))
    {
        return EchangeAccountNumber;
    }
    if (!this->vIBAN(IBAN))
    {
        return EchangeIBAN;
    }
    if (username != this->userLogin->username)
    {
        if (this->read(username))
        {
            return EchangeUsername;
        }
    }
    // validated now change user
    user *us = this->userLogin;
    us->name = name;
    us->ID = ID;
    us->accountNumber = accountNumber;
    us->IBAN = IBAN;
    QString pUsername = this->userLogin->username;
    us->username = username;
    this->replace(us, pUsername);

    return changed;
}

EchangePassword User::changePassword(QString &pereventPassword, QString &password, QString &confirmPassword)
{
    if (!this->vPassword(password))
    {
        return eVPassword;
    }
    if (!this->confirmedPassword(password, confirmPassword))
    {
        return eConfirmPassword;
    }
    if (this->hashPassword(pereventPassword) != this->userLogin->password)
    {
        return ePereventPassword;
    }
    this->userLogin->password = this->hashPassword(password);
    this->replace(this->userLogin);
    return changedPassword;
}

user *User::getUserLogin()
{
    return this->userLogin;
}

bool User::isLogin()
{
    return (bool)this->userLogin;
}

void User::logout()
{
    this->userLogin = 0;
}

bool User::accountIsSet()
{
    return !this->userLogin->ID.isEmpty();
}

void User::chargeAccount(int money)
{
    if (this->userLogin->debtAmount >= money)
    {
        this->userLogin->debtAmount -= money;
    }
    else
    {
        money -= this->userLogin->debtAmount;
        this->userLogin->debtAmount = 0;
        this->userLogin->money += money;
    }
    this->replace(this->userLogin);
}

EGetMoney User::getMoney(int mmoney)
{
    if (this->userLogin->debtAmount)
    {
        return haveDebtAmount;
    }
    if (this->userLogin->money < mmoney)
    {
        return MoreThanInventory;
    }
    this->userLogin->money -= mmoney;
    this->replace(this->userLogin);
    return getedMoney;
}

int User::showMoney()
{
    return this->userLogin->money - this->userLogin->debtAmount;
}

bool User::withdrawAccount(int mmoney)
{
    if (this->userLogin->money >= mmoney)
    {
        this->userLogin->debtAmount -= mmoney;
        this->replace(this->userLogin);
        return true;
    }
    mmoney -= this->userLogin->money;
    if (this->vDebtAmount(this->userLogin->debtAmount + mmoney))
    {
        this->userLogin->money = 0;
        this->userLogin->debtAmount += mmoney;
        this->replace(this->userLogin);
        return true;
    }
    return false;
}

QString User::userStructToString(user *us)
{
    QString tString = "";

    tString += us->ID;
    tString += ",";
    tString += us->name;
    tString += ",";
    tString += us->username;
    tString += ",";
    tString += us->password;
    tString += ",";
    tString += us->accountNumber;
    tString += ",";
    tString += us->IBAN;
    tString += ",";
    tString += QString::number(us->debtAmount);
    tString += ",";
    tString += QString::number(us->money);
    tString += '\n';

    return tString;
}

user *User::read(QString &username)
{
    user *tUser = nullptr;

    QFile file(this->pathFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return tUser;

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
        QStringList list = line.split(",");

        if (username == list[2])
        {
            tUser = new user;
            tUser->ID = list[0];
            tUser->name = list[1];
            tUser->username = list[2];
            tUser->password = list[3];
            tUser->accountNumber = list[4];
            tUser->IBAN = list[5];
            tUser->debtAmount = list[6].toInt();
            tUser->money = list[7].toInt();
            break;
        }
    }
    file.flush();
    file.close();
    return tUser;
}

bool User::save(user *us)
{
    QFile file(this->pathFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return false;

    QTextStream out(&file);
    out << this->userStructToString(us);
    file.flush();
    file.close();
    return true;
}

bool User::replace(user *us, QString pUsername)
{

    if (pUsername == "")
    {
        pUsername = us->username;
    }

    QString str, temp1 = "", temp2 = "";

    QFile readFile(this->pathFile);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&readFile);
    bool ok = false;
    short int temp = 1;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(",");

        if (ok && pUsername == list[2])
        {
            temp = 2;
        }
        else
        {
            if (temp == 1)
            {
                temp1 += line + '\n';
            }
            else
            {
                temp2 += line + '\n';
            }
        }

        if (!ok)
        {
            ok = true;
        }
    }
    str = temp1 + this->userStructToString(us) + temp2;

    readFile.flush();
    readFile.close();

    QFile writeFile(this->pathFile);
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&writeFile);
    out << str;
    writeFile.flush();
    writeFile.close();

    return true;
}
