#include "GUI_Triviador.h"


GUI_Triviador::GUI_Triviador(QWidget* parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    m_pRegister = nullptr;
    m_Lobby = nullptr;
    QObject::connect(m_pRegister, &Register::finished, this, &GUI_Triviador::on_registerFinished);
}

GUI_Triviador::~GUI_Triviador()
{
    delete m_pRegister;
    delete m_Lobby;
}


void GUI_Triviador::on_LoginButton_clicked()
{
    std::string username = ui->NameLogin->text().toUtf8().constData();
    std::string password = ui->PasswordLogin->text().toUtf8().constData();
    
    if (ui->NameLogin->text().isEmpty())
    {
        QMessageBox::warning(this, "Can't loggin", "The username is not filled in.", QMessageBox::Button::Ok); // modal window
        return;
    }
    if (ui->PasswordLogin->text().isEmpty())
    {
        QMessageBox::warning(this, "Can't loggin", "The password is not filled in.", QMessageBox::Button::Ok); // modal window
        return;
    }
    
    crow::json::wvalue body = { {"username", username}, {"password", password} };

    auto responseRegister = cpr::Post(
        cpr::Url{ "http://localhost:18080/login" },
        cpr::Body{ body.dump() }

    );
    if (responseRegister.status_code == 200) {
        QMessageBox::information(this, "Dialog", "Login succesful!", QMessageBox::Button::Ok); // modal window
        m_Lobby = new Lobby(username);
        m_Lobby->setModal(true);
        m_Lobby->show();
        this->close();
        return;
        
    }
    else {
        QMessageBox::warning(this, "Dialog", "Invalid username or password please try again!", QMessageBox::Button::Ok); // modal window
        return;
    }
    
    //Verificare daca exista in baza de date ;
    //ui->NameLoggin->text().toStdString()
    // Ca sa iei vloarea
    //Pornire lobby
    //Lobby lobby;
    //lobby.setModal(true);
    //lobby.exec();


}


void GUI_Triviador::on_CancelButton_clicked()
{
    int result = QMessageBox::question(this, "Leave", "Do you really want to leave?", QMessageBox::Button::Yes, QMessageBox::Button::No);
    //verificare ce a alfes
    if (result == QMessageBox::Button::Yes) {
        //exit(0);  // exit with status code 0 (indicating success)
        this->close();
    }
    if (result == QMessageBox::Button::No || result == QMessageBox::Rejected) {
        this->setVisible(true);  // show the current window or dialog
    }
    
}

void GUI_Triviador::on_RegisterButton_clicked()
{
    m_pRegister = new Register;
    m_pRegister->setModal(true);
    m_pRegister->show();
}


void GUI_Triviador::on_registerFinished()
{
    m_pRegister->setModal(false);
}
/*
void GUI_Triviador::closeEvent(QCloseEvent* event)
{
    // Create a message box with a question and two buttons (Yes and No)
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Exit", "Are you sure you want to exit?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
}
*/
