#include "QuestionMultipleChoice.h"

QuestionMultipleChoice::QuestionMultipleChoice(const std::string& text, const std::string& answer, const std::array<std::string, 4>& choices)
	:Question(text,answer),
	m_choices(choices)
{
}

QuestionMultipleChoice::QuestionMultipleChoice(const QuestionMultipleChoice& Q)
{
	this->m_text = Q.m_text;
	this->m_answer = Q.m_answer;
	this->m_choices = Q.m_choices;
}

const std::array<std::string, 4>& QuestionMultipleChoice::GetChoices() const
{
	return m_choices;
}
