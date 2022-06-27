#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include "user.h"

namespace Ui
{
    class BaseWindow;
}

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaseWindow(User *myUser, QWidget *parent = nullptr);
    ~BaseWindow();

private:
    Ui::BaseWindow *ui;
    User *myUser;
};

#endif // BASEWINDOW_H
