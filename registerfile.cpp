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

// push sign up
void RegisterFile::on_pushButton_clicked()
{
    QString confirmPassword = ui->lineEdit_confirm_password->text();
    QString password = ui->lineEdit_password->text();
    QString username = ui->lineEdit_username->text();

    // use Register function in User class
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

// push sign in
void RegisterFile::on_pushButton_2_clicked()
{
    this->goToSingnInPage();
}

// go to sign in page
void RegisterFile::goToSingnInPage()
{
    this->deleteUserClass();
    hide();
    this->mainWindow = new MainWindow(this);
    this->mainWindow->show();
}

// delete the User object
void RegisterFile::deleteUserClass()
{
    delete this->myUser;
    this->myUser = 0;
}
