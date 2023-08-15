#pragma once
#include <string>

class MatchH
{
public:
	MatchH() = default;
	MatchH(int winsNumber, int losesNumber);
	MatchH(const MatchH& matchH);

	int GetWinsNumber() const;
	int GetLosesNumber() const;

	friend std::ostream& operator<<(std::ostream& out, const MatchH& matchH);

	virtual ~MatchH() = default;
protected:
	int m_winsNumber;
	int m_losesNumber;
};

