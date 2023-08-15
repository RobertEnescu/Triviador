#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "TriviadorDatabase.h"
#include <ctime>
#include <cstdlib>

namespace sql = sqlite_orm;
int main()
{
	std::vector<std::vector<std::pair<int,int>>>m_map;

	const std::string db_file = "triviador_database.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();
	/*auto initNumberOfMatches = db.count<Matches>();
	if (initNumberOfMatches == 0)
		populateStorage(db);*/
	auto initNumberOfQuestions = db.count<dbClasses::Question>();
	auto initNumberOfQuestionsMultipleChoice = db.count<dbClasses::QuestionMultipleChoice>();
	if (initNumberOfQuestions == 0)
		populateStorageQuestions(db);
	if (initNumberOfQuestionsMultipleChoice == 0)
		populateStorageQuestionsMultipleChoice(db);
	
    crow::SimpleApp Triviador;

    CROW_ROUTE(Triviador, "/") ([]() {
		return "Testare Server";
		});
	CROW_ROUTE(Triviador,"/game")([]() {
		return "Game page";
		});
	CROW_ROUTE(Triviador, "/history")([&db]() {
		std::vector <crow::json::wvalue> MatchesJson;
		for (const auto& match : db.iterate<dbClasses::Matches>())
		{
			MatchesJson.push_back(crow::json::wvalue
				{
					{"id", match.id},
					{"name", match.nume},
					{"no_players",match.no_players}
				}
			);
		}
		return crow::json::wvalue(MatchesJson);
		});
	CROW_ROUTE(Triviador, "/questions")([&db]() {
		std::vector <crow::json::wvalue> QuestionsJson;
	for (const auto& question : db.iterate<dbClasses::Question>())
	{
		QuestionsJson.push_back(crow::json::wvalue
			{
				{"id", question.id},
				{"text", question.text},
				{"answer",question.answer}
			}
		);
	}
	return crow::json::wvalue(QuestionsJson);
		});
	CROW_ROUTE(Triviador, "/GetHistoryWin")([&db](const crow::request& req) {
		auto payload = crow::json::load(req.body);
		std::string name = payload["name"].s();
		std::vector <crow::json::wvalue> History;
		for (const auto& matches : db.iterate<dbClasses::Matches>())
		{
			if(matches.nume==name)
			History.push_back(crow::json::wvalue
				{
					{"Result", matches.id},
				}
			);
		}
		return crow::json::wvalue(History);
		});
	CROW_ROUTE(Triviador, "/questionsmultiplechoice")([&db]() {
		std::vector <crow::json::wvalue> QuestionsMultipleChoiceJson;
	for (const auto& questionMultipleChoice : db.iterate<dbClasses::QuestionMultipleChoice>())
	{
		QuestionsMultipleChoiceJson.push_back(crow::json::wvalue
			{
				{"id", questionMultipleChoice.id},
				{"text", questionMultipleChoice.text},
				{"answer",questionMultipleChoice.answer},
				{"choice1",questionMultipleChoice.choice1},
				{"choice2",questionMultipleChoice.choice2},
				{"choice3",questionMultipleChoice.choice3},
				{"choice4",questionMultipleChoice.choice4}
			}
		);
	}
	return crow::json::wvalue(QuestionsMultipleChoiceJson);
		});
	CROW_ROUTE(Triviador, "/QmcAnswer").methods("POST"_method)([&db](const crow::request& req) {
		std::vector <crow::json::wvalue> QuestionsJson;
		auto payload = crow::json::load(req.body);
		int id = std::stoi(payload["id"].s());
		int answer= std::stoi (payload["answer"].s());
		for (const auto& question : db.iterate<dbClasses::Question>())
		{
			if (question.id == id)
			{
				if (question.answer == answer)
				return crow::response(200, "perfect answer");
				else
				{
					if(question.answer > answer)
						return crow::response(question.answer-answer,"This is the difference");
					else
						return crow::response(question.answer - answer, "This is the difference");
				}
				break;
			}
		}
		});
	CROW_ROUTE(Triviador, "/GetQuestion")([&db]() {
		srand(time(0));
		int ok = 0;
		int id = 1 + (rand() % 50);
		for (const auto& questionMultipleChoice : db.iterate<dbClasses::QuestionMultipleChoice>())
		{
			if (questionMultipleChoice.id == id)
			{
				ok = 1;
				crow::json::wvalue value(
					{
				{"id", questionMultipleChoice.id},
				{"text", questionMultipleChoice.text},
				{"answer",questionMultipleChoice.answer},
				{"choice1",questionMultipleChoice.choice1},
				{"choice2",questionMultipleChoice.choice2},
				{"choice3",questionMultipleChoice.choice3},
				{"choice4",questionMultipleChoice.choice4}
					}
				);
				return value;
				break;
			}
		}
		});
	CROW_ROUTE(Triviador, "/QAnswer").methods("POST"_method)([&db](const crow::request& req) {
		std::vector <crow::json::wvalue> QuestionsMultipleChoiceJson;
		auto payload = crow::json::load(req.body);
		int id = std::stoi(payload["id"].s());
		std::string answer = (payload["answer"].s());
		for (const auto& questionMultipleChoice : db.iterate<dbClasses::QuestionMultipleChoice>())
		{
			if (questionMultipleChoice.id == id)
			{
				if (questionMultipleChoice.answer == answer)
					return crow::response(200, "Good Answer");
				else
				{
					return crow::response(400, "Bad Answer");
					break;
				}
			}
		}
		});
	std::vector<std::string> loggedUsers;
	CROW_ROUTE(Triviador, "/login").methods("POST"_method)([&db, &loggedUsers](const crow::request& req) {
		auto payload = crow::json::load(req.body);
		auto username = payload["username"].s();
		auto password = payload["password"].s();
		for (const auto& player : db.iterate<dbClasses::Player>())
		{
			if (player.username == username)
			{
				if (player.password == password)
				{
					loggedUsers.push_back(username);
					return crow::response(200,"Succesful login");
				}
				return crow::response(400, "Wrong password,please try again");
			}
		}
		return crow::response(400, "Wrong username, please register");
	});
	CROW_ROUTE(Triviador, "/register").methods("POST"_method)([&db](const crow::request& req) {
		auto payload = crow::json::load(req.body);
		for (const auto& player : db.iterate<dbClasses::Player>())
		{
			if (player.username == payload["username"].s())
				return crow::response(400, "Username already taken");
		}
		dbClasses::Player player;
		player.username = payload["username"].s();
		player.password = payload["password"].s();
		player.lossesNumber = 0;
		player.winsNumber = 0;
		db.insert(player);
		return crow::response(200); 
	});

	std::map<std::string, std::pair<int, std::vector<std::string>>> rooms;
	CROW_ROUTE(Triviador, "/create_room").methods("POST"_method)([&rooms, &loggedUsers](const crow::request& req) {
		auto payload = crow::json::load(req.body);
	std::string room_name = payload["room_name"].s();
	int max_players = payload["max_players"].i();
	std::string creating_user = payload["username"].s();

	if (rooms.count(room_name) > 0) {
		return crow::response(400, "Room name already taken");
	}

	// Check if the creating user is logged in
	if (std::find(loggedUsers.begin(), loggedUsers.end(), creating_user) == loggedUsers.end()) {
		return crow::response(400, "You must be logged in to create a room");
	}

	std::vector<std::string> players(max_players);
	players[0] = creating_user;
	rooms[room_name] = std::make_pair(max_players, players);
	return crow::response(200);
		});

	CROW_ROUTE(Triviador, "/join_room").methods("POST"_method)([&rooms, &loggedUsers](const crow::request& req) {
		auto payload = crow::json::load(req.body);
	std::string room_name = payload["room_name"].s();
	std::string joining_user = payload["username"].s();

	// Check if the room exists
	if (rooms.count(room_name) == 0) {
		return crow::response(404, "Room not found");
	}

	// Check if the joining user is logged in
	if (std::find(loggedUsers.begin(), loggedUsers.end(), joining_user) == loggedUsers.end()) {
		return crow::response(400, "You must be logged in to join a room");
	}

	if (std::find(rooms[room_name].second.begin(), rooms[room_name].second.end(), joining_user) != rooms[room_name].second.end()) {
		return crow::response(400, "You are already in this room");
	}
	// Check if the room is full
	/*if (rooms[room_name].second.size() >= rooms[room_name].first) {
		return crow::response(400, "Room is full");
	}*/
	if (false) {
		return crow::response(400, "Room is full");
	}

	// Add the joining user to the room's player list
	rooms[room_name].second.push_back(joining_user);
	return crow::response(200);
		});

	CROW_ROUTE(Triviador, "/players_in_room/<string>").methods("GET"_method)([&rooms](const crow::request& req, std::string room_name) {
		if (rooms.count(room_name) == 0) {
			return crow::response(404, "Room not found");
		}
	std::string players_list;
	for (auto player : rooms[room_name].second) {
		if (player != "") {
			players_list += player + ",";
		}
	}
	players_list = players_list.substr(0, players_list.size() - 1); // remove the trailing comma
	return crow::response(200, players_list);
		});

	/*std::map<std::string, int> rooms;
	CROW_ROUTE(Triviador, "/create_room")
		.methods("POST"_method)
		([&rooms](const crow::request& req) {
		auto payload = crow::json::load(req.body);
	std::string room_name = payload["room_name"].s();
	int max_players = payload["max_players"].i();
	if (rooms.count(room_name) > 0) {
		return crow::response(400, "Room name already taken");
	}
	rooms[room_name] = max_players;
	return crow::response(200);
			});*/

	CROW_ROUTE(Triviador, "/list_rooms")
		([&rooms]() {
		std::stringstream room_list;
	room_list << "[";
	bool first = true;
	for (const auto& room : rooms)
	{
		if (!first) room_list << ",";
		room_list << "{\"name\":\"" << room.first << "\",\"max players\":" << room.second.first << "}";
		first = false;
	}
	room_list << "]";

	std::stringstream json_response;
	json_response << "{" << "\"status\":\"success\"" << ",\"rooms\":" << room_list.str() << "}";
	return json_response.str();
			});


	CROW_ROUTE(Triviador, "/game/start").methods("POST"_method)([&m_map](const crow::request& req) {
		auto payload = crow::json::load(req.body);
		int no_players = std::stoi(payload["no_players"].s());
		if (no_players == 2)
		{
			for (int i = 0; i < 3; i++)
			{
				std::vector<std::pair<int,int>> v1;
				for (int j = 0; j < 3; j++)
				{
					v1.push_back(std::make_pair(0,0));
				}
				m_map.push_back(v1);
			}

		}
		if (no_players == 3)
		{
			for (int i = 0; i < 5; i++)
			{
				std::vector<std::pair<int, int>> v1;
				for (int j = 0; j < 3; j++)
				{
					v1.push_back(std::make_pair(0, 0));
				}
				m_map.push_back(v1);
			}
		}
		if (no_players == 4)
		{
			for (int i = 0; i < 6; i++)
			{
				std::vector<std::pair<int, int>> v1;
				for (int j = 0; j < 4; j++)
				{
					v1.push_back(std::make_pair(0, 0));
				}
				m_map.push_back(v1);
			}
		}
		return crow::response(200, "Game started");
		});
	CROW_ROUTE(Triviador, "/game/update").methods("POST"_method)([&m_map](const crow::request& req) {
		auto payload = crow::json::load(req.body);
		int player_number = std::stoi(payload["player_number"].s());
		int no_players = std::stoi(payload["no_players"].s());
		int line = std::stoi(payload["line"].s());
		int collumn = std::stoi(payload["collumn"].s());
		int points = std::stoi(payload["points"].s());
		static int i = 1;
		if (player_number == i)
		{
			m_map[line][collumn].first = i;
			m_map[line][collumn].second = +points;
			i++;
			std::vector <crow::json::wvalue> MatchJson;
			for (int j = 0; j < m_map.size(); j++)
			{
				for (int k = 0; k < m_map[0].size(); k++)
				{
					MatchJson.push_back(crow::json::wvalue
						{
							{"Player_index", m_map[j][k].first},
							{"Score", m_map[j][k].second},
						}
					);
				}
			}
			return crow::json::wvalue(MatchJson);;
		}
		else if (player_number != i && player_number <= no_players)
		{
			std::vector <crow::json::wvalue> MatchJson;
			for (int j = 0; j < m_map.size(); j++)
			{
				for (int k = 0; k < m_map[0].size(); k++)
				{
					MatchJson.push_back(crow::json::wvalue
						{
							{"Player_index", m_map[j][k].first},
							{"Score", m_map[j][k].second},
						}
					);
				}
			}
			return crow::json::wvalue(MatchJson);
		}
		});

	Triviador.port(18080).multithreaded().run();
	
	return 0;
}
