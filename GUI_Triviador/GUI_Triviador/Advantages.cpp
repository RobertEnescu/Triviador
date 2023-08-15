#include "Advantages.h"

Advantages::Advantages(int numberOf5050, int chooseAnswer, int suggestAnswer)
	:m_numberOf5050(numberOf5050),
	m_chooseAnswer(chooseAnswer),
	m_suggestAnswer(suggestAnswer)
{

}

Advantages::Advantages(const Advantages& advantages)
{
	*this = advantages;
}

int Advantages::GetNumberOf5050() const
{
	return m_numberOf5050;
}

int Advantages::GetChooseAnswer() const
{
	return m_chooseAnswer;
}

int Advantages::GetSuggestAnswer() const
{
	return m_suggestAnswer;
}

void Advantages::SetNumberOf5050(int valoare)
{
	this->m_numberOf5050 = valoare;
}

void Advantages::SetNumberOfChoose(int valoare)
{
	this->m_chooseAnswer = valoare;
}

void Advantages::SetNumberOfSuggest(int valoare)
{
	this->m_suggestAnswer = valoare;
}

int Advantages::GetNumberOfAdvantages()
{
	int count = 0;
	if (this->m_numberOf5050 == 1)
	{
		count++;
	}
	if (this->m_chooseAnswer == 1)
	{
		count++;
	}
	if (this->m_suggestAnswer == 1)
	{
		count++;
	}
	return count;
}



std::ostream& operator<<(std::ostream& out, Advantages advantages)
{
	out << advantages.GetNumberOf5050() << advantages.GetChooseAnswer() << advantages.GetSuggestAnswer();
	return out;
}
