#include "Question.h"

Question::Question(const std::string& text, const std::string& answer) :m_text(text), m_answer(answer)
{
}

Question::Question(const Question& Q)
{
	this->m_text = Q.m_text;
	this->m_answer = Q.m_answer;
}

const std::string& Question::GetText() const
{
	return m_text;
}

const std::string& Question::GetAnswer() const
{
	return m_answer;
}
