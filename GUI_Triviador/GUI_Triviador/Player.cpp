#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>


Player::Player(const std::string& username, const std::string& password, const MatchH& matchH, const Advantages& advantages)
    :m_username(username),
    m_password(password),
    m_matchH(matchH),
    m_advantages(advantages)
{
}

Player::Player(const Player& player)
{
    *this = player;
}

const std::string& Player::GetUsername() const
{
    return m_username;
}

const std::string& Player::GetPassword() const
{
    return m_password;
}

const MatchH& Player::GetMatchH() const
{
    return m_matchH;
}

const Advantages& Player::GetAdvantages() const
{
    return m_advantages;
}

std::vector<Territory> Player::GetTerritories() const
{
    return m_territories;
}

void Player::SetTerritories(Territory territory)
{
    this->m_territories.push_back(territory);
}

void Player::UnsetTerritories(int numar)
{
    for (int k = numar; k < this->m_territories.size() - 1; k++)
    {
        this->m_territories[k] = this->m_territories[k + 1];
    }
    this->m_territories.pop_back();
}

void Player::ReplaceTerritory(int numar, Territory teritoriu)
{
    this->m_territories[numar] = teritoriu;
}

bool Player::IsUnique(const std::string& newUsername)
{
    std::ifstream in;
    in.open("Usernames.txt");
    std::string currentUsername;
    while (!in.eof())
    {
        std::getline(in, currentUsername);
        if (currentUsername == "")
        {
            in.close();
            return true;
        }
        if (currentUsername == newUsername)
        {
            in.close();
            return false;
        }
    }
    in.close();
    return true;
}

void Player::ChooseAdvantage(QuestionMultipleChoice question)
{
    int alegere;
    auto it = question.GetChoices().data();
    if (*it == "")
    {
        std::cout << "Avantaje disponibile: " << m_advantages.GetNumberOfAdvantages() << std::endl;
        std::cout << "Alege avantajul: " << std::endl;
        std::cout << "Apasa: " << std::endl;
        std::cout << "1-pentru ~alegere raspuns~" << std::endl;
        std::cout << "2-pentru ~sugerare raspuns~" << std::endl;
    }
    else
    {
        std::cout << "Avantaje disponibile: " << m_advantages.GetNumberOfAdvantages() << std::endl;
        std::cout << "Alege avantajul: " << std::endl;
        std::cout << "Apasa: " << std::endl;
        std::cout << "3-pentru 50-50." << std::endl;
    }

    std::cin >> alegere;
    if (alegere == 2)
    {
        SuggestAnswer(question);
        m_advantages.SetNumberOfSuggest(0);
    }
    if (alegere == 1)
    {
        ChooseAnswer(question);
        m_advantages.SetNumberOfChoose(0);
    }
    if (alegere == 3)
    {
        RemoveHalfOfAnswers(question);
        m_advantages.SetNumberOf5050(0);
    }
    int numar;
    bool sem = true;
    while (sem)
    {
        std::cout << "Alege teritoriul din care sa platesti avantajul." << "\n";
        std::cin >> numar;
        if (m_territories[numar].GetScore() > 100)
        {
            m_territories[numar].SetScore(m_territories[numar].GetScore() - 100);
            sem = false;
        }
        else
        {
            std::cout << "Teritoriul ales nu are destule puncte!"<<"\n";
        }
    }
}

void Player::SuggestAnswer(QuestionMultipleChoice question)
{
    int randomNumber = (rand() % 5) + 1;
    std::cout<<"\n" << "Valoare apropiata de raspuns: " << stoi(question.GetAnswer()) + randomNumber;
}

void Player::ChooseAnswer(Question question)
{
    int raspuns= stoi(question.GetAnswer());
    std::cout << "\n" << "Cele 4 variante de raspuns sunt: " << "\n";
    for (int i = 0; i < 4; i++)
    {
        std::cout << raspuns + i<<"\n";
    }
}

void Player::RemoveHalfOfAnswers(QuestionMultipleChoice question)
{
    std::array < std::string, 4 > a= question.GetChoices();
    a[0] = "";
    a[1] = "";
    std::cout << "Raspunsuri ramase dupa avantaj: ";
    std::cout << a[2] << " " << a[3];
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
    out << "Username-ul jucatorului este: "<<player.GetUsername()<<std::endl;
    out << "Parola jucatorului este: "<<player.GetPassword() << std::endl;  
    out << player.GetMatchH();
    return out;
}
