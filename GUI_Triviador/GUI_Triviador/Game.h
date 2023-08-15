#pragma once

#include <cstdint>
#include "Player.h"
#include <vector>
#include <queue>
#include "QuestionMultipleChoice.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include "Board.h"



#include "ui_Game.h"
#ifndef GAME_H
#define GAME_H

#include <QDialog>

namespace Ui {
    class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget* parent = nullptr);
    void set(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent*);

    void SetVector(std::pair<QPointF,QString> coord);
    void SetScore(int numar, int numar2);
    void SetPlayers(int numar);



	std::vector<Question> GetQuestions();
	std::vector<QuestionMultipleChoice> GetMQuestions();
	Board GetBoard();

	void SetCurrentPlayer(Player currentPlayer);
	void SetPlayers(std::vector<Player> players);
	void SetBoard(Board board);

	void Phase0SelectNumberOfPlayers();
	void Phase1SelectBase();
	void Phase2AssignTerritoriesToPlayers();
	void Phase3Fight();
	void Phase4SelectWinner();
	void ParseQuestions();
	void PrintQuestions();
	Question GetRandomQuestion();
	QuestionMultipleChoice GetRandomQuestionMultipleChoice();
	std::vector<Player> GetClasament(Question randomQuestion);
	void ChooseTerritory(std::vector<Player> clasament);
	void ChooseBase(std::vector<Player> clasament);
	int GetCurrentPlayer(Player player);
	bool IsNeighbours(std::vector<Territory> vector, int linie, int coloana);
	int FindSecondPlayer(int linie, int coloana);
	int FindTerritory(int player, int linie, int coloana);
	int UseAdvantage();
	~Game();

private slots:
	void on_Generate_clicked();
	void on_Submit_clicked();


private slots:
    void on_clear_clicked();

private:
    void mouseReleaseEvent(QMouseEvent* event) override;
    Ui::Game* ui;
    std::vector<std::pair<QPointF,QString>> m_vectorCoord;
    int m_linii=0;
    int m_coloane=0;
    //int m_players=0;
    std::vector<std::pair<int, int>> m_players;
    int m_scor = 0;
protected:
	Board m_board;
	Player m_currentPlayer;
	std::vector<Player> m_Players;
	std::vector<Question> m_Questions;
	std::vector<QuestionMultipleChoice> m_QuestionsMultipleChoice;
};

#endif // GAME_H


