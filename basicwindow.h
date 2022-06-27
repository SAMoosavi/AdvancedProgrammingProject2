#ifndef BASICWINDOW_H
#define BASICWINDOW_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class BasicWindow;
}

class BasicWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BasicWindow(User *myUser, QWidget *parent = nullptr);
    ~BasicWindow();

private:
    Ui::BasicWindow *ui;
    User *myUser;
};

#endif // BASICWINDOW_H
