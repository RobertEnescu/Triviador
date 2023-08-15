#pragma once
#include "Question.h"
#include <array>
class QuestionMultipleChoice :
    public Question
{
public:
    QuestionMultipleChoice() = default;
    QuestionMultipleChoice(const std::string& text, const std::string& answer, const std::array<std::string, 4>& choices);
    QuestionMultipleChoice(const QuestionMultipleChoice &Q);
    const std::array<std::string, 4>& GetChoices() const;
    virtual ~QuestionMultipleChoice() = default;
private:
    std::array<std::string, 4> m_choices;
};

