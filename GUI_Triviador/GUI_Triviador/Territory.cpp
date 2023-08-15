#include "Territory.h"

Territory::Territory(int player, bool isBase) :
	m_playerOcupation(player),
	m_base(isBase)
{
	if (isBase)
	{
		m_score = 3;
	}
	else
	{
		m_score = 1;
	}
	//static_assert(sizeof(this->m_playerOcupation) <= 2, "This class.playerocupation should be 2 byte in size");
}

Territory::Territory() :
	m_playerOcupation(0),
	m_base(false),
	m_score(0)
{
	//Empty;
}

void Territory::SetDefaut()
{
	m_playerOcupation = 0;
	m_base = false;
	m_score = 0;
}

int Territory::GetPlayerOcupation() const
{
	return m_playerOcupation;
}

std::pair<int, int> Territory::GetCoordinates() const
{
	return m_coordinates;
}




//void Territory::SetPlayerOcupation(Player_Ocupation player)
//{
//	m_playerOcupation = player;
//}

void Territory::SetCoordinates(std::pair<int, int>coordinates)
{
	this->m_coordinates = coordinates;
}

void Territory::SetPlayerOcupation(int player)
{
	//m_playerOcupation = static_cast<Territory::Player_Ocupation>(player);
	this->m_playerOcupation = player;
}

void Territory::SetIsbase(bool isBase)
{
	m_base = isBase;
}

uint16_t Territory::GetScore() const
{
	return m_score * 100;
}



void Territory::SetScore(uint16_t score)
{
	m_score = score/100;
}

void Territory::Add100Score()
{
	m_score++;
}

void Territory::Decrease100Score()
{
	m_score--;
}

Territory Territory::operator+(const uint8_t adding)
{
	m_score += adding / 100;
	return *this;
}

Territory Territory::operator++(int)
{
	Territory temp = *this;
	m_score++;
	return temp;
}

Territory Territory::operator--(int)
{
	Territory temp = *this;
	m_score--;
	return temp;
}

Territory& Territory::operator++()
{
	++m_score;
	return *this;
}

Territory& Territory::operator--()
{
	--m_score;
	return *this;
}

bool Territory::IsBase()
{

	return m_base;
}

std::ostream& operator<<(std::ostream& out, const Territory& territory)
{
	//return out << static_cast<int>(territory.m_playerOcupation) << " " << territory.m_base << " " << territory.m_score * 100 << " ";
	return out << static_cast<int>(territory.m_playerOcupation) << " " << territory.m_base << " " << territory.m_score << " ";
}