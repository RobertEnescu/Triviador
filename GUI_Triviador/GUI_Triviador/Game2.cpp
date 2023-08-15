#include "Game2.h"
#include <cpr/cpr.h>
#include <crow.h>
#include <chrono>
using namespace std::chrono;


Game2::Game2()
{

}

Game2::Game2(const Board& board, const Player& currentPlayer, const std::vector<Player> players, const std::vector<Question>& Questions, const std::vector<QuestionMultipleChoice>& QuestionsMultipleChoice) :
	m_board(board),
	m_currentPlayer(currentPlayer),
	m_Players(players),
	m_Questions(Questions),
	m_QuestionsMultipleChoice(QuestionsMultipleChoice)
{
}

std::vector<Question> Game2::GetQuestions()
{
	return m_Questions;
}

std::vector<QuestionMultipleChoice> Game2::GetMQuestions()
{
	return m_QuestionsMultipleChoice;
}

Board Game2::GetBoard()
{
	return m_board;
}

void Game2::SetCurrentPlayer(Player currentPlayer)
{
	this->m_currentPlayer = currentPlayer;
}

void Game2::SetPlayers(std::vector<Player> players)
{
	this->m_Players = players;
}

void Game2::SetBoard(Board board)
{
	this->m_board = board;
}

void Game2::Phase1SelectBase()
{
	std::cout << "Etapa alegerii bazei: " << "\n";

	Question randomQuestion = GetRandomQuestion();
	std::cout << randomQuestion.GetText() << "\n";
	auto start = high_resolution_clock::now();
	//std::cout<<"Numarul random este: " << distr(eng)<<"\n";

	std::vector<Player> clasament = GetClasament(randomQuestion);
	std::cout << "Raspunsul corect era: " << randomQuestion.GetAnswer() << "\n";
	std::cout << "Alegeti coordonatele bazei: " << "\n";
	ChooseBase(clasament);
}

void Game2::Phase2AssignTerritoriesToPlayers()
{
	while (!this->m_board.isFullyOccupied())
	{
		Question randomQuestion = GetRandomQuestion();
		std::cout << randomQuestion.GetText() << "\n";
		std::vector<Player> clasament = GetClasament(randomQuestion);
		std::cout << "Raspunsul corect era: " << randomQuestion.GetAnswer() << "\n";
		std::cout << "Alegeti coordonatele teritoriului: " << "\n";
		ChooseTerritory(clasament);
		GetBoard().ShowBoard();
	}
}

void Game2::Phase3Fight()
{
	int runde = 4;

	using duration = std::chrono::seconds;
	if (m_Players.size() % 2 == 0)
	{
		runde = 5;
	}
	for (int i = 0; i < runde; i++)
	{
		std::cout << "Runda numarul " << i + 1 << ": " << "\n";

		int linie, coloana;
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, m_Players.size() - 1);

		int jucator1 = distr(eng);
		bool sem = false;
		while (!sem)
		{
			std::cout << m_Players[jucator1].GetUsername() << " alege sa atace regiunea: " << "\n";
			std::cout << "Linie: " << "\n";
			std::cin >> linie;
			std::cout << "Coloana: " << "\n";
			std::cin >> coloana;

			for (int i = 0; i < m_Players.size(); i++)
			{
				std::cout << m_Players[i].GetUsername() << " ";
				for (int j = 0; j < m_Players[i].GetTerritories().size(); j++)
				{
					std::cout << m_Players[i].GetTerritories()[j].GetScore() << "-" << m_Players[i].GetTerritories()[j].GetCoordinates().first << ", " << m_Players[i].GetTerritories()[j].GetCoordinates().second << " ";
				}
				std::cout << std::endl;
			}


			if (IsNeighbours(m_Players[jucator1].GetTerritories(), linie, coloana))
			{
				sem = true;
				QuestionMultipleChoice randomQuestion = GetRandomQuestionMultipleChoice();
				std::string answer;
				std::string answer2;

				std::cout << randomQuestion.GetText() << "\n";
				for (int j = 0; j < randomQuestion.GetChoices().size(); j++)
				{
					std::cout << randomQuestion.GetChoices()[j] << "\n";
				}
				int opt = UseAdvantage();
				if (opt == 1)
				{
					if (m_Players[jucator1].GetAdvantages().GetNumberOf5050() > 0)
					{
						m_Players[jucator1].RemoveHalfOfAnswers(randomQuestion);
					}
				}
				std::cout << "Raspunsul jucatorului " << m_Players[jucator1].GetUsername() << "este: " << "\n";
				auto start1 = high_resolution_clock::now();
				std::cin >> answer;
				auto stop1 = high_resolution_clock::now();

				const duration d1 = duration_cast<duration>(stop1 - start1);
				int index = FindSecondPlayer(linie, coloana);
				opt = UseAdvantage();
				if (opt == 1)
				{
					if (m_Players[index].GetAdvantages().GetNumberOf5050() > 0)
					{
						m_Players[index].RemoveHalfOfAnswers(randomQuestion);
					}
				}
				std::cout << "Raspunsul jucatorului " << m_Players[index].GetUsername() << "este: " << "\n";
				auto start2 = high_resolution_clock::now();
				std::cin >> answer2;
				auto stop2 = high_resolution_clock::now();

				const duration d2 = duration_cast<duration>(stop2 - start2);

				std::cout << "Raspunsul corect era: " << randomQuestion.GetAnswer() << "\n";

				bool p1 = true;
				if (answer == answer2)
				{
					if (answer == randomQuestion.GetAnswer() && answer2 == randomQuestion.GetAnswer())
					{
						if (d2 < d1)
						{
							p1 = false;
						}
					}
				}

				if (answer == randomQuestion.GetAnswer() && p1)
				{
					int numar = FindTerritory(index, linie, coloana);
					if (m_Players[index].GetTerritories()[numar].GetScore() == 100)
					{
						std::cout << "salut";
						Territory territory = m_Players[index].GetTerritories()[numar];
						territory.SetPlayerOcupation(jucator1 + 1);
						this->m_board.SetElement(territory, linie, coloana);
						m_Players[index].UnsetTerritories(numar);
						m_Players[jucator1].SetTerritories(territory);
					}
					else
					{
						std::cout << "salut2";
						Territory teritoriu2 = m_Players[index].GetTerritories()[numar];
						teritoriu2.Decrease100Score();
						m_Players[index].ReplaceTerritory(numar, teritoriu2);
						this->m_board.SetElement(teritoriu2, linie, coloana);
					}
				}
				else
				{
					if (answer2 == randomQuestion.GetAnswer())
					{
						std::cout << "salut3";
						int numar = FindTerritory(index, linie, coloana);
						Territory teritoriu3 = m_Players[index].GetTerritories()[numar];
						teritoriu3.Add100Score();
						m_Players[index].ReplaceTerritory(numar, teritoriu3);
						this->m_board.SetElement(teritoriu3, linie, coloana);
					}
				}
				this->m_board.ShowBoard();
			}
			else
			{
				std::cout << "Teritoriul ales nu este vecin cu niciun teritoriu pe care il detineti sau este printre teritoriile dumneavoastra!" << "\n";
			}
		}
	}
}

void Game2::Phase4SelectWinner()
{
	std::cout << "Castigatorul este: ";
	int maxim = 0, index = 0;
	for (int i = 0; i < m_Players.size(); i++)
	{
		int scor = 0;
		for (int j = 0; j < m_Players[i].GetTerritories().size(); j++)
		{
			scor += m_Players[i].GetTerritories()[j].GetScore();
		}
		if (scor > maxim)
		{
			maxim = scor;
			index = i;
		}
	}
	Player castigator = m_Players[index];
	std::cout << castigator.GetUsername();
}

void Game2::ParseQuestions()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/questions" });
	auto questions = crow::json::load(response.text);
	for (const auto& question : questions)
	{
		Question question2(question["text"].s(), std::to_string(int(question["answer"])));
		this->m_Questions.push_back(question2);
	}
	cpr::Response response2 = cpr::Get(cpr::Url{ "http://localhost:18080/questionsmultiplechoice" });
	auto questions2 = crow::json::load(response2.text);
	for (const auto& question : questions2)
	{
		std::array<std::string, 4> array1;
		array1[0] = question["choice1"].s();
		array1[1] = question["choice2"].s();
		array1[2] = question["choice3"].s();
		array1[3] = question["choice4"].s();
		QuestionMultipleChoice question2(question["text"].s(), question["answer"].s(), array1);
		this->m_QuestionsMultipleChoice.push_back(question2);
	}
}

void Game2::PrintQuestions()
{
	std::vector<QuestionMultipleChoice> tmp_q = m_QuestionsMultipleChoice;
	for (int i = 0; i < tmp_q.size(); i++)
	{
		std::cout << tmp_q[i].GetText() << " " << tmp_q[i].GetAnswer() << "\n";
		for (size_t j = 0; j < 4; j++)
		{
			std::cout << tmp_q[i].GetChoices().at(j) << " ";
		}
		std::cout << "\n";
	}
	std::vector<Question> tmp_q2 = m_Questions;
	for (int i = 0; i < tmp_q2.size(); i++)
	{
		std::cout << tmp_q2[i].GetText() << " " << tmp_q2[i].GetAnswer() << "\n";
	}
	std::cout << "\n";
}

Question Game2::GetRandomQuestion()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, this->m_Questions.size() - 1);

	std::vector<Question> questions = this->m_Questions;
	int index = 0;
	int n = distr(eng);
	std::cout << n << "\n";
	Question randomQuestion(questions[n]);
	return randomQuestion;
}

QuestionMultipleChoice Game2::GetRandomQuestionMultipleChoice()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, this->m_QuestionsMultipleChoice.size() - 1);

	std::vector<QuestionMultipleChoice> questions = this->m_QuestionsMultipleChoice;
	int index = 0;
	int n = distr(eng);
	std::cout << n << "\n";
	QuestionMultipleChoice randomQuestion(questions[n]);
	return randomQuestion;
}

std::vector<Player> Game2::GetClasament(Question randomQuestion)
{
	using duration = std::chrono::seconds;
	std::vector<std::pair<std::pair<int, duration>, int>> diferentaSiTimp;

	for (int i = 0; i < m_Players.size(); i++)
	{
		int difference, answer;
		std::cout << "Raspunsul jucatorului " << m_Players[i].GetUsername() << " este: " << "\n";
		auto start = high_resolution_clock::now();
		std::cin >> answer;
		auto stop = high_resolution_clock::now();
		const duration d = duration_cast<duration>(stop - start);
		//std::cout << "Timpul in care a raspuns este: " << d << "\n";

		difference = abs(stoi(randomQuestion.GetAnswer()) - answer);


		std::pair<std::pair<int, duration>, int> pMare;
		std::pair<int, duration> pMic;
		pMic.first = difference;
		pMic.second = d;
		pMare.first = pMic;
		pMare.second = i;
		diferentaSiTimp.push_back(pMare);
	}
	std::vector<Player> clasament;

	std::sort(diferentaSiTimp.begin(), diferentaSiTimp.end());
	for (int i = 0; i < diferentaSiTimp.size() - 1; i++)
	{
		if (diferentaSiTimp[i].first.first == diferentaSiTimp[i + 1].first.first)
		{
			if (diferentaSiTimp[i + 1].first.second < diferentaSiTimp[i].first.second)
			{
				std::pair<std::pair<int, duration>, int> aux = diferentaSiTimp[i + 1];
				diferentaSiTimp[i + 1] = diferentaSiTimp[i];
				diferentaSiTimp[i] = aux;
			}
		}
	}

	for (int i = 0; i < diferentaSiTimp.size(); i++)
	{
		std::cout << m_Players[diferentaSiTimp[i].second].GetUsername() << "\n";
		clasament.push_back(m_Players[diferentaSiTimp[i].second]);
	}
	return clasament;
}

void Game2::ChooseTerritory(std::vector<Player> clasament)
{
	for (int i = 0; i < clasament.size(); i++)
	{
		for (int j = 0; j < clasament.size() - i - 1; j++)
		{
			int linie, coloana;
			std::cout << clasament[i].GetUsername() << " :" << "\n";
			std::cout << "Linie: " << "\n";
			std::cin >> linie;
			std::cout << "Coloana: " << "\n";
			std::cin >> coloana;
			int number = GetCurrentPlayer(clasament[i]);
			Territory territory2 = this->m_board.GetTerritory(linie, coloana);
			std::pair<int, int> indici;

			indici.first = linie;
			indici.second = coloana;
			territory2.SetIsbase(false);
			territory2.SetPlayerOcupation(number + 1);
			territory2.SetCoordinates(indici);
			this->m_board.SetElement(territory2, linie, coloana);
			if (this->m_board.ZoneAsign(linie, coloana))
			{
				std::cout << "Zona ocupata cu succes!" << "\n";
				this->m_Players[number].SetTerritories(this->m_board.GetTerritory(linie, coloana));
			}
			else
			{
				std::cout << "Aceasta regiune este ocupata de alt jucator!" << "\n";
				j--;
			}
		}
	}
}

void Game2::ChooseBase(std::vector<Player> clasament)
{
	for (int i = 0; i < clasament.size(); i++)
	{
		int linie, coloana;
		std::cout << clasament[i].GetUsername() << " :" << "\n";
		std::cout << "Linie: " << "\n";
		std::cin >> linie;
		std::cout << "Coloana: " << "\n";
		std::cin >> coloana;
		int number = GetCurrentPlayer(clasament[i]);
		Territory territory2 = this->m_board.GetTerritory(linie, coloana);
		std::pair<int, int> indici;

		indici.first = linie;
		indici.second = coloana;
		territory2.SetIsbase(true);
		territory2.SetPlayerOcupation(number + 1);
		territory2.SetCoordinates(indici);
		this->m_board.SetElement(territory2, linie, coloana);
		if (this->m_board.ZoneAsign(linie, coloana))
		{
			std::cout << "Zona ocupata cu succes!" << "\n";
			this->m_Players[number].SetTerritories(this->m_board.GetTerritory(linie, coloana));
		}
		else
		{
			std::cout << "Aceasta regiune este ocupata de alt jucator!" << "\n";
			i--;
		}
	}
}

int Game2::GetCurrentPlayer(Player player)
{
	for (int i = 0; i < this->m_Players.size(); i++)
	{
		if (this->m_Players[i].GetUsername() == player.GetUsername())
		{
			return i;
		}
	}
	return 0;
}

bool Game2::IsNeighbours(std::vector<Territory> vector, int linie, int coloana)
{
	for (int i = 0; i < vector.size(); i++)
	{
		if (abs(vector[i].GetCoordinates().first - linie) + abs(vector[i].GetCoordinates().second - coloana) == 1)
		{
			return true;
		}
	}
	return false;
}

int Game2::FindSecondPlayer(int linie, int coloana)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		for (int j = 0; j < m_Players[i].GetTerritories().size(); j++)
		{
			if (m_Players[i].GetTerritories()[j].GetCoordinates().first == linie && m_Players[i].GetTerritories()[j].GetCoordinates().second == coloana)
			{
				return i;
			}
		}
	}
	return 100;
}

int Game2::FindTerritory(int player, int linie, int coloana)
{
	for (int i = 0; i < m_Players[player].GetTerritories().size(); i++)
	{
		if (m_Players[player].GetTerritories()[i].GetCoordinates().first == linie && m_Players[player].GetTerritories()[i].GetCoordinates().second == coloana)
		{
			return i;
		}
	}
	return 100;
}

int Game2::UseAdvantage()
{
	int opt;
	std::cout << "Vrei sa folosesti un avantaj?" << "\n";
	std::cout << "1-pentru Da" << "\n";
	std::cout << "2-pentru Nu" << "\n";
	std::cin >> opt;
	return opt;
}
