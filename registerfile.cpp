#include "registerfile.h"
#include "ui_registerfile.h"

RegisterFile::RegisterFile(User * myUser,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterFile)
{
    ui->setupUi(this);
    this->myUser  = myUser;
    this->showImg();
}

void RegisterFile::showImg(){
    QPixmap pix(":/img/images/register.png");
    int w = 500;
    int h = 300;
    ui->label_img->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

RegisterFile::~RegisterFile()
{
    delete ui;
}

void RegisterFile::on_pushButton_clicked()
{
   QString confirmPassword = ui->lineEdit_confirm_password->text();
   QString password = ui->lineEdit_password->text();
   QString username = ui->lineEdit_username->text();

  switch(this->myUser->Register(username,password,confirmPassword)){
      case registered:
      qDebug() << "hi";
      break;
  case EVPassword:
      qDebug() << "EVPassword";
      break;
  case EConfirmPassword:
      qDebug() << "EConfirmPassword";
      break;
  case notAvailableUsername:
      qDebug() << "notAvailableUsername";
      break;
  default:
      qDebug() << "bay";
  }
}

