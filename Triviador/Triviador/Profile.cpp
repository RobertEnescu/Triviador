#include "Profile.h"
#include <iostream>

Profile::Profile(int winsNumber, int losesNumber)
	: m_winsNumber(winsNumber),
	m_losesNumber(losesNumber)
{
}

Profile::Profile(const Profile& profile)
{
	*this = profile;
}

int Profile::GetWinsNumber() const
{
	return m_winsNumber;
}

int Profile::GetLosesNumber() const
{
	return m_losesNumber;
}

std::ostream& operator<<(std::ostream& out, const Profile& profile)
{
	out << "Numarul de meciuri castigate: " << profile.GetWinsNumber() <<std::endl;
	out << "Numarul de meciuri pierdute: " << profile.GetLosesNumber() << std::endl;
	return out;
}
