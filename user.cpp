#include "user.h"
using namespace std;

vector<user*> User::users = {};

User::User()
{
}
User::~User() {}

user *User::searchUser(QString &username)
{
   for (auto us : users)
   {
       if (us->username == username)
       {
           return us;
       }
   }
   return nullptr;
}

bool User::vPassword(QString &password)
{
    string a = password.toStdString();
    const regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*(\\W|_))(?=^\\S*$).{8,}$");
    return regex_match(a, pattern);
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
    return name.length() <= 40;
}

bool User::vID(QString &ID)
{
    return ID.length() == 10;
}

bool User::vAccountNumber(QString &accountNumber)
{
    return accountNumber.length() == 10;
}

bool User::vIBAN(QString &IBAN)
{
    return IBAN[0] == 'I' && IBAN[1] == 'R' && IBAN.length() == 12;
}

bool User::vDebtAmount(int debtAmount)
{
    return debtAmount <= 10e6;
}

ERegister User::Register(QString &username, QString &password, QString &confirmPassword)
{
   if (!this->searchUser(username))
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
   user *a = new user;
   a->username = username;
   a->password = this->hashPassword(password);
   this->users.push_back(a);
   return registered;
}

ELogin User::login(QString &username, QString &password)
{
   user *a = this->searchUser(username);
   if (!a)
   {
       return notFuond;
   }
   if (this->hashPassword(password) != a->password)
   {
       return notCorrectPassword;
   }
   this->userLogin = a;
   return logined;
}

ESetAccount User::setAccount(QString &name, QString &ID, QString &accountNumber, QString &IBAN)
{
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
    user *a = this->userLogin;
    a->name = name;
    a->ID = ID;
    a->accountNumber = accountNumber;
    a->IBAN = IBAN;

    return setedAccount;
}

bool User::chengeName(QString &name)
{
    if (!this->vName(name))
    {
        return false;
    }
    this->userLogin->name = name;
    return true;
}

bool User::chengeID(QString &ID)
{
    if (!this->vID(ID))
    {
        return false;
    }
    this->userLogin->ID = ID;
    return true;
}

bool User::chengeAccountNumber(QString &accountNumber)
{
    if (!this->vAccountNumber(accountNumber))
    {
        return false;
    }
    this->userLogin->accountNumber = accountNumber;
    return true;
}

bool User::chengeIBAN(QString &IBAN)
{
    if (!this->vIBAN(IBAN))
    {
        return false;
    }
    this->userLogin->IBAN = IBAN;
    return true;
}

bool User::chengeUsername(QString &username)
{
   if (this->searchUser(username))
   {
       return false;
   }
   this->userLogin->username = username;
   return true;
}

EChengePassword User::chengePassword(QString &password, QString &confirmPassword)
{
    if (!this->vPassword(password))
    {
        return eVPassword;
    }
    if (!this->confirmedPassword(password, confirmPassword))
    {
        return eConfirmPassword;
    }
    this->userLogin->password = password;
    return chengedPassword;
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
        this->userLogin->dabtMoney += money;
    }
}

EGetMoney User::getMoney(int money)
{
    if (this->userLogin->debtAmount)
    {
        return haveDebtAmount;
    }
    if (this->userLogin->dabtMoney < money)
    {
        return MoreThanInventory;
    }
    this->userLogin->dabtMoney -= money;
    return getedMoney;
}

bool User::withdrawAccount(int money)
{
    if (this->userLogin->dabtMoney >= money)
    {
        this->userLogin->debtAmount -= money;
        return true;
    }
    money -= this->userLogin->dabtMoney;
    if (this->vDebtAmount(this->userLogin->debtAmount + money))
    {
        this->userLogin->dabtMoney = 0;
        this->userLogin->debtAmount += money;
        return true;
    }
    return false;
}

// bool buyStock(stock* buyStock,int number);
// bool saleStock(stock* saleStock,int number);

// vector<stock *> getStock();

// bool save();
// bool read();
