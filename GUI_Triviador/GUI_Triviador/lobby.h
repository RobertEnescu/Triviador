#ifndef LOBBY_H
#define LOBBY_H

#include <QListWidget>
#include <iostream>
#include <QDialog>
#include <vector>
#include <string>
#include "Player.h"
#include "Game.h"
#include <QMessageBox>
#include <cpr/cpr.h>
#include <crow.h>


namespace Ui {
class Lobby;
}

class Lobby : public QDialog
{
    Q_OBJECT

public:
    explicit Lobby(std::string username,QWidget *parent = nullptr);//Sa notezi ce trebe aici, daca e nullptr nu e bine;
    ~Lobby();
public:
    std::vector<Player> GetPlayers(int index);
    void AddLobby(Player host);
private slots:
    void on_AddLobby_clicked();


    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();


    void on_ListLobbyW_itemClicked(QListWidgetItem *item);

    void on_ListLobbyW_itemChanged(QListWidgetItem* item);
    void on_refresh_clicked();
    void on_show_clicked();
    // trebuie sa aflam care din funtiile de mai sus e mai buna

private:
    Ui::Lobby *ui;
    std::vector<std::vector<Player>> m_Lobbys;
    std::string m_username;
    Game* m_game;
    // idk daca asta trebe aici sau il salvam pe server( lista de lobiuri)
    //plus sa vedem in ce e cel mai bine sa le salvam

};

#endif // LOBBY_H
