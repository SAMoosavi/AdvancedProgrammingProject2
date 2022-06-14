#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
//#include <Q>

MainWindow::MainWindow(User * myUser,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->myUser = myUser;
    ui->setupUi(this);
    showImg();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showImg(){
    QPixmap pix(":/img/images/login.png");
    int w = 500;
    int h = 300;
    ui->label_img->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
   switch(this->myUser->login(username,password)){
       case logined:
       qDebug() << "hi";
       break;
   case notFuond:
       qDebug() << "not";
       break;
   case notCorrectPassword:
       qDebug() << "notCorrectPassword";
       break;
   default:
       qDebug() << "bay";

   }
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "bbb";
}

