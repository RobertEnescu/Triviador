#pragma once
#include <string>

class Profile
{
public:
	Profile() = default;
	Profile(int winsNumber, int losesNumber);
	Profile(const Profile& profile);

	int GetWinsNumber() const;
	int GetLosesNumber() const;

	friend std::ostream& operator<<(std::ostream& out, const Profile& profile);

	virtual ~Profile() = default;
protected:
	int m_winsNumber;
	int m_losesNumber;
};

