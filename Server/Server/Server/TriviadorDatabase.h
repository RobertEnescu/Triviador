#pragma once
#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;
namespace dbClasses {

	class Matches {
	public:
		int id;
		std::string nume;
		int no_players;
		int win;
	};
	class Question {
	public:
		int id;
		std::string text;
		int answer;
	};
	class QuestionMultipleChoice {
	public:
		int id;
		std::string text;
		std::string answer;
		std::string choice1;
		std::string choice2;
		std::string choice3;
		std::string choice4;
	};
	class Player{
	public:
		int playerID;
		std::string username;
		std::string password;
		int winsNumber;
		int lossesNumber;
	};

}
inline auto createStorage(const std::string& filename)
{
	using namespace dbClasses;
	return sql::make_storage(
		filename,
		sql::make_table(
			"Matches",
			sql::make_column("id", &Matches::id, sql::autoincrement(), sql::primary_key()),
			sql::make_column("name", &Matches::nume),
			sql::make_column("no_players", &Matches::no_players),
			sql::make_column("Result", &Matches::win)
		),
		sql::make_table(
			"Question",
			sql::make_column("id", &Question::id, sql::autoincrement(), sql::primary_key()),
			sql::make_column("text", &Question::text),
			sql::make_column("answer", &Question::answer)
		),
		sql::make_table(
			"QuestionMultipleChoice",
			sql::make_column("id", &QuestionMultipleChoice::id, sql::autoincrement(), sql::primary_key()),
			sql::make_column("text", &QuestionMultipleChoice::text),
			sql::make_column("answer", &QuestionMultipleChoice::answer),
			sql::make_column("choice1", &QuestionMultipleChoice::choice1),
			sql::make_column("choice2", &QuestionMultipleChoice::choice2),
			sql::make_column("choice3", &QuestionMultipleChoice::choice3),
			sql::make_column("choice4", &QuestionMultipleChoice::choice4)
		),
		sql::make_table(
			"Player",
			sql::make_column("playerID", &Player::playerID, sql::autoincrement(), sql::primary_key()),
			sql::make_column("username", &Player::username),
			sql::make_column("password", &Player::password),
			sql::make_column("winsNumber", &Player::winsNumber),
			sql::make_column("lossesNumber", &Player::lossesNumber)
		)
	);
};

using Storage = decltype(createStorage(""));

void populateStorageQuestions(Storage& storage);
void populateStorageQuestionsMultipleChoice(Storage& storage);

class TriviadorDatabase
{
public:
	TriviadorDatabase(Storage& storage);

private:
	Storage& m_db;
};

