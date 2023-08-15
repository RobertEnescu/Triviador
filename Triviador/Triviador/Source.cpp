#include <iostream>
#include <fstream>
#include <queue>
#include "QuestionMultipleChoice.h"
#include "Profile.h"
#include "Player.h"
#include "Board.h"
#include "Territory.h"
#include "Game.h"
#include "Advantages.h"
//#include "../Logging/Logger.h"

int main()
{
	//Logger log(std::cout, Logger::Level::Info);
	//log.Log(Logger::Level::Warning, " Ana");
	////testare daca un username este unic
	//Profile profil5(6,5);
	////Player player5("Nume7", "parola", profil5);
	//std::ofstream of;
	//of.open("Usernames.txt", std::ios::app);
	////if (player5.IsUnique(player5.GetUsername()))
	////{
	////	of <<std::endl<< player5.GetUsername();
	////	std::cout <<std::endl<< "Username-ul a fost adaugat cu succes!";
	////}
	////else
	////{
	////	std::cout <<std::endl<< "Username-ul introdus este folosit deja!";
	////}
	//of.close();
	//std::cout << "\n";
	//if (board.isFullyOccupied())
	//{
	//	std::cout << "Harta ocupata complet";
	//}
	//else std::cout << "Harta neocupata";

	//Advantages ad(1,1,0);
	//std::cout << ad << ad.GetNumberOfAdvantages()<<"\n\n\n\n";
	//
	//Sleep(1000);
	//log.Log(Logger::Level::Error, "Ana are ", 7, "mere");

	//std::array<std::string, 4> a;
	//a[0] = "a";
	//a[1] = "b";
	//a[2] = "c";
	//a[3] = "d";
	//QuestionMultipleChoice q34("Salut","2",a);
	//Profile profil(3,3);
	//Advantages avantaje(1,1,1);
	//Territory t1, t2, t3;
	//t1.SetScore(100);
	//t2.SetScore(200);
	//t3.SetScore(100);
	//Player p1("alex", "salut", profil, avantaje);
	//p1.SetTerritories(t1);
	//p1.SetTerritories(t2);
	//p1.SetTerritories(t3);
	//p1.ChooseAdvantage(q34);
	//std::cout <<"salut" << t2.GetScore();
	Profile profil;
	Advantages avantaj(1,1,1);
	Player player1("PLayer1","parola",profil,avantaj);
	Player player2("PLayer2","parola1",profil,avantaj);
	Player player3("PLayer3","parola2",profil,avantaj);
	Player player4("PLayer4","parola3",profil,avantaj);
	std::vector<Player> players;
	players.push_back(player1);
	players.push_back(player2);
	//players.push_back(player3);
	/*players.push_back(player3);
	players.push_back(player4);*/

	Game game;
	Board board(2);
	board.ShowBoard();
	game.ParseQuestions();
	game.SetCurrentPlayer(player1);
	game.SetPlayers(players);
	game.SetBoard(board);
	game.Phase1SelectBase();
	game.GetBoard().ShowBoard();
	game.Phase2AssignTerritoriesToPlayers();
	game.Phase3Fight();
	//game.GetBoard().ShowBoard();
	game.Phase4SelectWinner();
	//game.GetBoard().ShowBoard();
	/*Territory t1, t2, t3, t4;
	t1.SetScore(100);
	t2.SetScore(200);
	t3.SetScore(100);
	t4.SetScore(100);
	player1.SetTerritories(t1);
	player1.SetTerritories(t2);
	player2.SetTerritories(t3);
	player2.SetTerritories(t4);
	game.Phase4SelectWinner();*/
}