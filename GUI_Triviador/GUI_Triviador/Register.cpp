#include "Register.h"

Register::Register(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::RegisterUi)
{
    
    ui->setupUi(this);
}

Register::~Register()
{
    //emit finished(true);
    delete ui;
}

void Register::on_RegisterButton_clicked()
{
    
    std::string username = ui->UsernameCheck->text().toUtf8().constData();
    std::string password = ui->PasswordCheck->text().toUtf8().constData();

    if (ui->UsernameCheck->text().isEmpty())
    {
        QMessageBox::warning(this, "Can't register", "The username is not filled in.", QMessageBox::Button::Ok); // modal window
        return;
    }
    if (ui->PasswordCheck->text().isEmpty())
    {
        QMessageBox::warning(this, "Can't register", "The password is not filled in.", QMessageBox::Button::Ok); // modal window
        return;
    }

    crow::json::wvalue body = { {"username", username}, {"password", password} };

    auto responseRegister = cpr::Post(
        cpr::Url{ "http://localhost:18080/register" },
        cpr::Body{ body.dump() }

    );
    if (responseRegister.status_code == 200) {
        QMessageBox::information(this, "Register successful", "Thanks!", QMessageBox::Button::Ok); // modal window
        return;
        //de trimis playeru la meniul principal
    }
    else {
        QMessageBox::warning(this, "Can't register", "Username taken.", QMessageBox::Button::Ok); // modal window
        return;
    }
}

void Register::on_CancelButton_clicked()
{
    int result = QMessageBox::question(this, "Leave", "Do you really want to leave?", QMessageBox::Button::Yes, QMessageBox::Button::No);
    //verificare ce a alfes
    if (result == QMessageBox::Button::Yes) {
        //exit(0);  
        this->close();
    }
    if (result == QMessageBox::Button::No || result == QMessageBox::Rejected) {
        this->setVisible(true);  // show the current window or dialog
    }

}

void Register::on_LoginButton_clicked()
{
    this->close();
}
