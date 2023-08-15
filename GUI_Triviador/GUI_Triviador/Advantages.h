#pragma once
#include <iostream>
#include <vector>
class Advantages
{
public:
	Advantages() = default;
	Advantages(int numberOf5050, int chooseAnswer, int suggestAnswer);
	Advantages(const Advantages& advantages);

	int GetNumberOf5050() const;
	int GetChooseAnswer() const;
	int GetSuggestAnswer() const;

	void SetNumberOf5050(int valoare);
	void SetNumberOfChoose(int valoare);
	void SetNumberOfSuggest(int valoare);

	int GetNumberOfAdvantages();

	friend std::ostream& operator<<(std::ostream& out, Advantages advantages);

	virtual ~Advantages()=default;
private:
	int m_numberOf5050;
	int m_chooseAnswer;
	int m_suggestAnswer;
};

