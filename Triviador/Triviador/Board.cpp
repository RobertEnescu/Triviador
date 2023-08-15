#include "Board.h"
#include <conio.h>
#include <windows.h>

//Board::Board()
//{
//
//}

Board::Board(int nrPlayers):
	m_noPlayers(nrPlayers)
{
	GenerateBoard(nrPlayers);
}

int Board::GetNoPlayers()
{
	return m_noPlayers;
}

Territory Board::GetTerritory(int linie, int coloana)
{
	return m_map[linie][coloana];
}

void Board::SetElement(Territory territory, int linie, int coloana)
{
	this->m_map[linie][coloana] = territory;
}

void Board::GenerateBoard(int noPlayers)
{
		if (noPlayers == 2)
		{
			for (int i = 0; i < 3; i++)
			{
				std::vector<Territory> v1;
				for (int j = 0; j < 3; j++)
				{
					
					Territory T;
					v1.push_back(T);
				}
				m_map.push_back(v1);
			}

		}
		if (noPlayers == 3)
		{
			for (int i = 0; i < 5; i++)
			{
				std::vector<Territory> v1;
				for (int j = 0; j < 3; j++)
				{
					Territory T;
					v1.push_back(T);
				}
				m_map.push_back(v1);
			}
		}
		if (noPlayers == 4)
		{
			for (int i = 0; i < 6; i++)
			{
				std::vector<Territory> v1;
				for (int j = 0; j < 4; j++)
				{
					Territory T;
					v1.push_back(T);
				}
				m_map.push_back(v1);
			}
		}
}

void Board::ShowBoard()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < m_map.size(); i++)
	{
		for (int j = 0; j < m_map[i].size(); j++)
		{
			if (m_map[i][j].GetPlayerOcupation() == 1)
			{
				SetConsoleTextAttribute(console, 4); //red
			}
			if (m_map[i][j].GetPlayerOcupation() == 2)
			{
				SetConsoleTextAttribute(console, 1); //blue
			}
			if (m_map[i][j].GetPlayerOcupation() == 3)
			{
				SetConsoleTextAttribute(console, 6); //yellow
			}
			if (m_map[i][j].GetPlayerOcupation() == 4)
			{
				SetConsoleTextAttribute(console, 2); //green
			}
			std::cout << m_map[i][j].GetScore() << " ";
			SetConsoleTextAttribute(console, 7);
		}
		std::cout << '\n';
	}
}

bool Board::ZoneAsign(int linie, int coloana)
{
	if (this->m_map[linie][coloana].GetScore()== 0)
	{
		if (this->m_map[linie][coloana].IsBase())
		{
			m_map[linie][coloana].SetScore(300);
		}
		else
		{
			m_map[linie][coloana].SetScore(100);
		}
		return true;
	}
	return false;
}

bool Board::isFullyOccupied()
{
	for (int i = 0; i < m_map.size(); i++)
	{
		for (int j = 0; j < m_map[0].size(); j++)
		{
			if (m_map[i][j] .GetScore() == 0)
			{
				return false;
			}
		}
	}
	return true;
}


