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
    explicit buySaleStock( QWidget *parent = nullptr);
    ~buySaleStock();

private:
    Ui::buySaleStock *ui;
    User *myUser = new User();
};

#endif // BUYSALESTOCK_H
