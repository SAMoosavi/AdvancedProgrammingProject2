#include "mainwindow.h"
#include "user.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    User *myUser = new User;
    QApplication a(argc, argv);
    MainWindow w(myUser);
    w.show();
    return a.exec();
}
