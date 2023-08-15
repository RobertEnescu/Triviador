#include "Profile.h"
#include <iostream>

MatchH::MatchH(int winsNumber, int losesNumber)
	: m_winsNumber(winsNumber),
	m_losesNumber(losesNumber)
{
}

MatchH::MatchH(const MatchH& matchH)
{
	*this = matchH;
}

int MatchH::GetWinsNumber() const
{
	return m_winsNumber;
}

int MatchH::GetLosesNumber() const
{
	return m_losesNumber;
}

std::ostream& operator<<(std::ostream& out, const MatchH& matchH)
{
	out << "Numarul de meciuri castigate: " << matchH.GetWinsNumber() <<std::endl;
	out << "Numarul de meciuri pierdute: " << matchH.GetLosesNumber() << std::endl;
	return out;
}
