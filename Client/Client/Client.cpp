#include <iostream>
#include <filesystem>
#include <numeric>
#include <sstream>
#include <memory>
#include <regex>
#include <string>
#include <cpr/cpr.h>    
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "../../Server/Server/Server/TriviadorDatabase.h"
namespace sql = sqlite_orm;
int main()
{

    std::string no_players = "2";
    std::string player = "2";

    crow::json::wvalue body = { {"player_number", player},{"no_players",no_players},{"line","0"},{"collumn","1"},{"points","200"} };
    auto responseRegister = cpr::Post(
        cpr::Url{ "http://localhost:18080/game/update" },
        cpr::Body{ body.dump() }
    );
    responseRegister.text;



   /* std::string id = "1";
    std::string answer = "Anglia";
    crow::json::wvalue body = { {"id", id}, {"answer", answer} };

    auto responseRegister = cpr::Post(
        cpr::Url{ "http://localhost:18080/QAnswer" },
        cpr::Body{ body.dump() }

    );
    if (responseRegister.status_code == 200)
        std::cout << "Raspuns perfect";
    else
        std::cout << "Raspuns gresit";*/
    /*std::string id = "1";
    std::string answer = "300";
    crow::json::wvalue body = { {"id", id}, {"answer", answer} };

    auto responseRegister = cpr::Post(
        cpr::Url{ "http://localhost:18080/QmcAnswer" },
        cpr::Body{ body.dump() }

    );
    if (responseRegister.status_code == 200)
        std::cout << "Raspuns perfect";
    else
        std::cout << "Diferenta este" << responseRegister.status_code;*/ //Testare functie pt raspuns intrebari
    /*std::string username;
    std::string password;
    bool done = false;

    std::cout << "1. Register\n";
    std::cout << "2. Login\n";
        
    int choice;
    while (std::cin >> choice) {
        if (choice == 1 || choice == 2) {
            break;
        }

        std::cout << "Please try again.";
    }
    std::cout << "Username:\n";
    std::cin >> username;
    std::cout << "Password:\n";
    std::cin >> password;

    crow::json::wvalue body = { {"username", username}, {"password", password} };


    if (choice == 1) {
        auto responseRegister = cpr::Post(
            cpr::Url{ "http://localhost:18080/register" },
            cpr::Body{ body.dump() }

        );
        if (responseRegister.status_code == 200) {
            std::cout << "Register succesful! :)\n";
        }
        else {
            std::cout << "Username is not unique.\n";
        }

    }
    else {
        auto responseRegister = cpr::Post(
            cpr::Url{ "http://localhost:18080/login" },
            cpr::Body{ body.dump() }

        );
        if (responseRegister.status_code == 200) {
            std::cout << "Login succesful! :)\n";
        }
        else {
            std::cout << "Invalid username or password.\n";
        }
    }*/

    return 0;
}
