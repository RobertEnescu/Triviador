#pragma once
#include <string>

class Question
{
public:
	Question() = default;
	Question(const std::string& text, const std::string& answer);
	Question(const Question &Q);
	const std::string& GetText() const;
	const std::string& GetAnswer() const;
	virtual ~Question() = default;
protected:
	std::string m_text;
	std::string m_answer;
};

