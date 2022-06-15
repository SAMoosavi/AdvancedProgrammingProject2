#ifndef SETACCOUNT_H
#define SETACCOUNT_H

#include <QMainWindow>

namespace Ui {
class SetAccount;
}

class SetAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetAccount(QWidget *parent = nullptr);
    ~SetAccount();

private:
    Ui::SetAccount *ui;
};

#endif // SETACCOUNT_H
