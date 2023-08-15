#pragma once

#include <stdint.h>
#include <iostream>

class Territory
{
public:
	enum class Player_Ocupation : uint8_t
	{
		None,
		Player_1,
		Player_2,
		Player_3,
		Player_4
	};

public:
	Territory(int player, bool isBase);
	Territory();
	void SetDefaut();

	int GetPlayerOcupation() const;
	std::pair<int, int> GetCoordinates() const;


	//void SetPlayerOcupation(Player_Ocupation player);
	void SetCoordinates(std::pair<int, int>coordinates);
	void SetPlayerOcupation(int player);
	void SetIsbase(bool isBase);

	uint16_t GetScore() const;
	void SetScore(const uint16_t score=1);
	void Add100Score();
	void Decrease100Score();
	Territory operator + (const uint8_t adding);
	Territory operator ++ (int);
	Territory operator -- (int);
	Territory& operator ++ ();
	Territory& operator -- ();

	bool IsBase();

	friend std::ostream& operator << (std::ostream& out, const Territory& territory);







private:
	uint16_t m_score;// the score is stored in modulo 100;
	bool m_base;
	int m_playerOcupation;// sau chimbam cu uint8_t
	std::pair<int, int> m_coordinates;
};

