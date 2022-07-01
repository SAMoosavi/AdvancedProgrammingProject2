#include "registerfile.h"
#include "ui_registerfile.h"

RegisterFile::RegisterFile(QWidget *parent) : QMainWindow(parent),
                                                            ui(new Ui::RegisterFile)
{
    ui->setupUi(this);
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

    switch (this->myUser->Register(username, password, confirmPassword))
    {
    case registered:
        QMessageBox::information(this, "Sign Up", "You are signed up");
        this->goToSingnInPage();
        break;
    case EVPassword:
        QMessageBox::critical(this, "Error", "Your password is not strong enough!");
        break;
    case EConfirmPassword:
        QMessageBox::critical(this, "Error", "Your confirm password is not correct!");
        break;
    case notAvailableUsername:
        QMessageBox::critical(this, "Error", "Your username is not available!");
        break;
    default:
        QMessageBox::warning(this, "?", "?");
    }
}

void RegisterFile::on_pushButton_2_clicked()
{
    this->goToSingnInPage();
}

void RegisterFile::goToSingnInPage()
{
    this->deleteUserClass();
    hide();
    this->mainWindow = new MainWindow(this);
    this->mainWindow->show();
}

void RegisterFile::deleteUserClass()
{
    delete this->myUser;
    this->myUser = 0;
}
