#pragma once
#include <vector>
#include <iostream>
#include "Territory.h"
class Board
{
public:
	Board()=default;
	Board(int nrPlayers);
	int GetNoPlayers();
	Territory GetTerritory(int linie, int coloana);
	void SetElement(Territory territory, int linie, int coloana);
	void GenerateBoard(int noPlayers);
	void ShowBoard();
	bool ZoneAsign(int linie, int coloana);
	bool isFullyOccupied();
private:
	std::vector<std::vector<Territory>> m_map;
	int m_noPlayers;
};

