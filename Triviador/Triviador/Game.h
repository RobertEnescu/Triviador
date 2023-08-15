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
class Game
{
public:
	enum class GamePhase : uint8_t
	{
		SelectBase,
		ConquerTerritory,
		Duel
	};
	Game();
	Game(const Board&  board, const Player &currentPlayer, const std::vector<Player> players,const std::vector<Question>& Questions,const std::vector<QuestionMultipleChoice>& QuestionsMultipleChoice);
	
	std::vector<Question> GetQuestions();
	std::vector<QuestionMultipleChoice> GetMQuestions();
	Board GetBoard();

	void SetCurrentPlayer(Player currentPlayer);
	void SetPlayers(std::vector<Player> players);
	void SetBoard(Board board);

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
	int FindTerritory(int player,int linie, int coloana);
	int UseAdvantage();

	virtual ~Game() = default;
protected:
	Board m_board;
	Player m_currentPlayer;
	std::vector<Player> m_Players;
	std::vector<Question> m_Questions;
	std::vector<QuestionMultipleChoice> m_QuestionsMultipleChoice;

};

