#include "user.h"
using namespace std;
#include <QDebug>
user *User::userLogin = 0;
User::User()
{
}
User::~User() {}

bool User::vPassword(QString &password)
{
    // Check if password has upper and lower case letters, numbers, spesial characters and at least 8 letters
    string a = password.toStdString();
    const regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*(\\W|_))(?=^\\S*$).{8,}$");
    return regex_match(a, pattern);

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

QString User::createUserID()
{
    QString id = "";

    // Set a random number as starting point
    srand((unsigned)time(0));
    for (int i = 0; i < 10; i++)
    {
        // Get a random number
        id += QString::number(rand() % 10);
    }
    return id;
}

bool User::vName(QString &name)
{
    // maximum 40 characters
    return name.length() <= 40;
}

bool User::vID(QString &ID)
{
    // 10 characters
    return ID.length() == 10;
}

bool User::vAccountNumber(QString &accountNumber)
{
    // 10 characters
    return accountNumber.length() == 10;
}

bool User::vIBAN(QString &IBAN)
{
    // check the IR in the first and 12 characters
    return IBAN[0] == 'I' && IBAN[1] == 'R' && IBAN.length() == 12;
}

bool User::vDebtAmount(int debtAmount)
{
    // maximum 1,000,000
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
    us->userID = this->createUserID();
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
    // validation
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

    // validated now change password
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

QString User::userStructToString(user *us)
{
    QString tString = "";

    tString += us->userID;
    tString += ",";
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

    // open file
    QFile file(this->pathFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return tUser;

    QTextStream in(&file);
    bool ok = false;

    // read file line by line
    while (!in.atEnd())
    {
        if (!ok)
        {
            ok = true;
            continue;
        }
        QString line = in.readLine();
        QStringList list = line.split(",");

        // if this username create the user
        if (username == list[3])
        {
            tUser = new user;
            tUser->userID = list[0];
            tUser->ID = list[1];
            tUser->name = list[2];
            tUser->username = list[3];
            tUser->password = list[4];
            tUser->accountNumber = list[5];
            tUser->IBAN = list[6];
            tUser->debtAmount = list[7].toDouble();
            tUser->money = list[8].toDouble();
            break;
        }
    }

    // close file
    file.flush();
    file.close();
    return tUser;
}

bool User::save(user *us)
{
    // open file
    QFile file(this->pathFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return false;

    QTextStream out(&file);

    // write new user
    out << this->userStructToString(us);
    file.flush();
    file.close();
    return true;
}

bool User::replace(user *us, QString pUsername)
{
    // set pUsername
    if (pUsername == "")
    {
        pUsername = us->username;
    }

    QString str, temp1 = "", temp2 = "";

    // open file
    QFile readFile(this->pathFile);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&readFile);
    bool ok = false;
    short int temp = 1;

    // read file line by line
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(",");

        // if this username go to temp2
        if (ok && pUsername == list[3])
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

    // close file
    readFile.flush();
    readFile.close();

    // create str for writing
    str = temp1 + this->userStructToString(us) + temp2;

    // open file
    QFile writeFile(this->pathFile);
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
