#include "registerfile.h"
#include "ui_registerfile.h"

RegisterFile::RegisterFile(User * myUser,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterFile)
{
    ui->setupUi(this);
    this->myUser  = myUser;
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


void RegisterFile::on_pushButton_2_clicked()
{
    hide();
    this->mainWindow = new MainWindow(this->myUser,this);
    this->mainWindow->show();
}

