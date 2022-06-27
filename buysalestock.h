#ifndef BUYSALESTOCK_H
#define BUYSALESTOCK_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class buySaleStock;
}

class buySaleStock : public QMainWindow
{
    Q_OBJECT

public:
    explicit buySaleStock(User *myUser, QWidget *parent = nullptr);
    ~buySaleStock();

private:
    Ui::buySaleStock *ui;
    User *myUser;
};

#endif // BUYSALESTOCK_H
