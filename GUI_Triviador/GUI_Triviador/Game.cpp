#include "Game.h"
#include <iostream>
#include <QPainter>
#include <QMouseEvent>
#include <QAbstractButton>
#include <string>



#include <cpr/cpr.h>
#include <crow.h>
#include <chrono>
using namespace std::chrono;

Game::Game(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
	ui->raspuns1->hide();
	ui->Submit->hide();
	ui->question->hide();
	ui->Generate->setVisible(false);
	ui->corect->hide();
	ui->corect2->hide();
	ui->diferenta->hide();
	ui->raspuns_jucator->hide();
	ui->scor->hide();
}

void Game::set(QWidget* parent)
{
    ui = new Ui::Game;
    ui->setupUi(this);
}

void Game::paintEvent(QPaintEvent*)
{
	Phase0SelectNumberOfPlayers();
	//update();
	
    //QPainter p(this);
    //QPen pen;
    //p.drawText(20,40,"Cati jucatori sunt?");
    //if (ui->two->isChecked() && this->m_players.size()==0)
    //{
    //    m_linii = 3;
    //    m_coloane = 3;
    //    SetPlayers(2);
    //}
    //if (ui->three->isChecked())
    //{
    //    m_linii = 5;
    //    m_coloane = 3;
    //    SetPlayers(3);
    //}
    //if (ui->four->isChecked())
    //{
    //    m_linii = 6;
    //    m_coloane = 4;
    //    SetPlayers(4);
    //}
    //for (int i = 0; i < m_linii; i++)
    //{
    //    for (int j = 0; j < m_coloane; j++)
    //    {
    //        QRect r(100+30*j,100+30*i,30,30);
    //        std::string aux=std::to_string(i)+" "+std::to_string(j);
    //        p.drawRect(r);
    //        p.drawText(r, Qt::AlignCenter,QString::fromStdString(aux));
    //    }
    //}
    //QString s,s1,s2;
    //for (int i = 0; i < m_players.size(); i++)
    //{
    //    s = "Player "+QString::number(i+1);
    //    p.drawText(400+60*i,50,s);
    //    s2 = "Scor=" + QString::number(m_players[i].second);
    //    p.drawText((400+60*i),65,s2);
    //}
    //s1 = "Scor total= " + QString::number(m_scor);
    //p.drawText(460,80,s1);

    ////if (ui->player->text()=="1")
    ////{
    ////    pen.setColor(Qt::red);
    ////    p.setPen(pen);
    ////    //int jx = (m_vectorCoord[m_vectorCoord.size() - 1].x() - 100) / 30, jy = (m_vectorCoord[m_vectorCoord.size() - 1].y() - 100) / 30;
    ////    QRect r(100 + 30 * jx, 100 + 30 * jy, 30, 30);
    ////    //QRect r(100,100,30,30);
    ////    p.drawRect(r);
    ////    pen.setColor(Qt::black);
    ////    p.setPen(pen);
    ////}


    //for (int i = 0; i < this->m_vectorCoord.size(); i++)
    //{
    //    if (this->m_vectorCoord[i].second == "1")
    //    {
    //        pen.setColor(Qt::red);
    //        p.setPen(pen);
    //        QRect r(100 + 30 * m_vectorCoord[i].first.x(), 100 + 30 * m_vectorCoord[i].first.y(), 30, 30);
    //        p.fillRect(r, Qt::red);
    //        p.drawRect(r);
    //        pen.setColor(Qt::black);
    //        p.setPen(pen);
    //        p.drawRect(r);
    //    }
    //    if (this->m_vectorCoord[i].second == "2")
    //    {
    //        pen.setColor(Qt::blue);
    //        p.setPen(pen);
    //        //int jx = (this->m_vectorCoord[i].first.x() - 100) / 30, jy = (this->m_vectorCoord[i].first.y() - 100) / 30;
    //        QRect r(100 + 30 * m_vectorCoord[i].first.x(), 100 + 30 * m_vectorCoord[i].first.y(), 30, 30);
    //        p.fillRect(r, Qt::blue);
    //        p.drawRect(r);
    //        pen.setColor(Qt::black);
    //        p.setPen(pen);
    //        p.drawRect(r);
    //    }
    //    if (this->m_vectorCoord[i].second == "3")
    //    {
    //        pen.setColor(Qt::yellow);
    //        p.setPen(pen);
    //        //int jx = (this->m_vectorCoord[i].first.x() - 100) / 30, jy = (this->m_vectorCoord[i].first.y() - 100) / 30;
    //        QRect r(100 + 30 * m_vectorCoord[i].first.x(), 100 + 30 * m_vectorCoord[i].first.y(), 30, 30);
    //        p.fillRect(r, Qt::yellow);
    //        p.drawRect(r);
    //        pen.setColor(Qt::black);
    //        p.setPen(pen);
    //        p.drawRect(r);
    //    }
    //    if (this->m_vectorCoord[i].second == "4")
    //    {
    //        pen.setColor(Qt::green);
    //        p.setPen(pen);
    //        //int jx = (this->m_vectorCoord[i].first.x() - 100) / 30, jy = (this->m_vectorCoord[i].first.y() - 100) / 30;
    //        QRect r(100 + 30 * m_vectorCoord[i].first.x(), 100 + 30 * m_vectorCoord[i].first.y(), 30, 30);
    //        p.fillRect(r, Qt::green);
    //        p.drawRect(r);
    //        pen.setColor(Qt::black);
    //        p.setPen(pen);
    //        p.drawRect(r);
    //    }
    //}

    //update();
}


void Game::mouseReleaseEvent(QMouseEvent* ev)
{
	if (!ui->Submit->isEnabled() && !ui->scor->isVisible())
	{
		if (ev->button() == Qt::RightButton)
		{
			ui->scor->setVisible(true);
			Territory teritoriu;
			int x= (ev->position().x() - 100) / 30, y= (ev->position().y() - 100) / 30;
			teritoriu.SetPlayerOcupation(1);
			this->m_board.SetElement(teritoriu,y,x);
			QString s = "Scor: "+QString::number(300);
			ui->scor->setText(s);
		}
	}

    //if (!ui->player->text().isEmpty())
    //{
    //    if (ev->button() == Qt::RightButton)
    //    {
    //        std::pair<QPointF, QString> element;
    //        int jx = (ev->position().x() - 100) / 30, jy = (ev->position().y() - 100) / 30;
    //        element.first.setX(jx);
    //        element.first.setY(jy);
    //        element.second = ui->player->text();

    //        if (!ui->isbase->text().isEmpty())
    //        {
    //            SetScore(ui->isbase->text().toInt(), ui->player->text().toInt());
    //        }
    //        bool sem = false;

    //        for (int i = 0; i < m_vectorCoord.size(); i++)
    //        {
    //            if (element.first.x() == m_vectorCoord[i].first.x() && element.first.y() == m_vectorCoord[i].first.y()) 
    //            {
    //                sem = true;
    //            }
    //        }

    //        if ((ev->position().x() > 100 && ev->position().x() < 100 + 30 * m_coloane) && (ev->position().y() > 100 && ev->position().y() < 100 + 30 * m_linii))
    //        {
    //            if (!sem && element.second.toInt()<=m_players.size())
    //            {
    //                SetVector(element);
    //            }
    //        }
    //    }
    //   
    //   /* QRect g(coord.x(), coord.y(), 10, 10);
    //    std::cout<<int((coord.y()-100)/30)<<"  "<<int((coord.x()-100)/30)<<"\n";*/
    //}
    //update();
}


void Game::SetVector(std::pair<QPointF, QString> coord)
{
    this->m_vectorCoord.push_back(coord);
}

void Game::SetScore(int numar, int numar2)
{
    if (numar == 1)
    {
        this->m_scor += 300;
        this->m_players[numar2-1].second=this->m_players[numar2-1].second+300;
    }
    else
    {
        this->m_scor += 100;
        this->m_players[numar2-1].second = this->m_players[numar2-1].second + 100;
    }
}

void Game::SetPlayers(int numar)
{
    for (int i = 0; i < numar; i++)
    {
        std::pair<int, int> p;
        p.first = i + 1;
        p.second = 0;
        this->m_players.push_back(p);
    }
}

void Game::on_clear_clicked()
{
    m_vectorCoord.clear();
    update();
}







std::vector<Question> Game::GetQuestions()
{
	return m_Questions;
}

std::vector<QuestionMultipleChoice> Game::GetMQuestions()
{
	return m_QuestionsMultipleChoice;
}

Board Game::GetBoard()
{
	return m_board;
}

void Game::SetCurrentPlayer(Player currentPlayer)
{
	this->m_currentPlayer = currentPlayer;
}

void Game::SetPlayers(std::vector<Player> players)
{
	this->m_Players = players;
}

void Game::SetBoard(Board board)
{
	this->m_board = board;
}

void Game::Phase0SelectNumberOfPlayers()
{
	//QPaintEvent* ev;
	QPainter p(this);
	if (ui->two->isVisible())
	{
		p.drawText(20, 40, "Cati jucatori sunt?");
		int number = 0;
		if (ui->two->isChecked())
		{
			number = 2;
		}
		if (ui->three->isChecked())
		{
			number = 3;
		}
		if (ui->four->isChecked())
		{
			number = 4;
		}
		if (number != 0)
		{
			Board board(number);
			SetBoard(board);
			board.ShowBoard(this);
			//update();
			ui->two->setVisible(false);
			ui->three->setVisible(false);
			ui->four->setVisible(false);
			//update();
			MatchH profil;
			Advantages avantaj(1, 1, 1);
			Player player1("PLayer1", "parola", profil, avantaj);
			Player player2("PLayer2", "parola1", profil, avantaj);
			Player player3("PLayer3", "parola2", profil, avantaj);
			Player player4("PLayer4", "parola3", profil, avantaj);
			std::vector<Player> players;
			switch (number)
			{
			case 2:
			{
				players.push_back(player1);
				players.push_back(player2);
				break;
			}
			case 3:
			{
				players.push_back(player1);
				players.push_back(player2);
				players.push_back(player3);
				break;
			}
			case 4:
			{
				players.push_back(player1);
				players.push_back(player2);
				players.push_back(player3);
				players.push_back(player4);
				break;
			}
			}
			ParseQuestions();
			SetCurrentPlayer(player1);
			SetPlayers(players);
			ui->Generate->setVisible(true);
		}
	}
	else
	{
		Phase1SelectBase();
	}
	this->m_board.ShowBoard(this);
	//update();
	
}

void Game::Phase1SelectBase()
{
	QPainter p(this);
	p.drawText(300,40,"Etapa alegerii bazei");
	update();
	
	if (ui->question->text() == "" && !ui->Generate->isEnabled())
	{
		Question randomQuestion = GetRandomQuestion();
		ui->question->setText(randomQuestion.GetText().c_str());
		QString s = "Raspunsul corect este: ";
		QString correct = randomQuestion.GetAnswer().c_str();
		ui->corect->setText(s);
		ui->corect2->setText(correct);
	}
	//if (!ui->Submit->isVisible())
	//{
	
	//	p.drawText(300, 100, randomQuestion.GetText().c_str());
	//	//ui->Generate->setEnabled(true);
	//}
	//update();
	//std::cout << "Etapa alegerii bazei: " << "\n";

	//Question randomQuestion = GetRandomQuestion();
	////std::cout << randomQuestion.GetText() << "\n";
	//p.drawText(300, 100, randomQuestion.GetText().c_str());
	////p.drawText(300, 120, QString::number(this->m_Players.size()));
	//if (!ui->raspuns1->isVisible())
	//{
	//	switch(this->m_Players.size())
	//	{
	//	case 2:
	//	{
	//		ui->raspuns1->setVisible(true);
	//		ui->raspuns2->setVisible(true);
	//		break;
	//	}
	//	case 3:
	//	{
	//		ui->raspuns1->setVisible(true);
	//		ui->raspuns2->setVisible(true);
	//		ui->raspuns3->setVisible(true);
	//		break;
	//	}
	//	case 4:
	//	{
	//		ui->raspuns1->setVisible(true);
	//		ui->raspuns2->setVisible(true);
	//		ui->raspuns3->setVisible(true);
	//		ui->raspuns4->setVisible(true);
	//		break;
	//	}
	//	case 0:
	//	{
	//		break;
	//	}
	//	}
	//	update();
	//}
	//if (ui->raspuns1->isVisible())
	//{
	//	p.drawText(420, 260, "Player 1");
	//}
	//if (ui->raspuns2->isVisible())
	//{
	//	p.drawText(420, 260, "Player 1");
	//	p.drawText(550, 260, "Player 2");
	//}
	//if (ui->raspuns3->isVisible())
	//{
	//	p.drawText(420, 260, "Player 1");
	//	p.drawText(550, 260, "Player 2");
	//	p.drawText(420, 310, "Player 3");
	//}
	//if (ui->raspuns4->isVisible())
	//{
	//	p.drawText(420, 260, "Player 1");
	//	p.drawText(550, 260, "Player 2");
	//	p.drawText(420, 310, "Player 3");
	//	p.drawText(550, 310, "Player 4");
	//}
	
	//auto start = high_resolution_clock::now();
	////std::cout<<"Numarul random este: " << distr(eng)<<"\n";

	//std::vector<Player> clasament = GetClasament(randomQuestion);
	//std::cout << "Raspunsul corect era: " << randomQuestion.GetAnswer() << "\n";
	//std::cout << "Alegeti coordonatele bazei: " << "\n";
	//ChooseBase(clasament);
}

void Game::Phase2AssignTerritoriesToPlayers()
{
	while (!this->m_board.isFullyOccupied())
	{
		Question randomQuestion = GetRandomQuestion();
		std::cout << randomQuestion.GetText() << "\n";
		std::vector<Player> clasament = GetClasament(randomQuestion);
		std::cout << "Raspunsul corect era: " << randomQuestion.GetAnswer() << "\n";
		std::cout << "Alegeti coordonatele teritoriului: " << "\n";
		ChooseTerritory(clasament);
		GetBoard().ShowBoard(this);
	}
}

void Game::Phase3Fight()
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
				this->m_board.ShowBoard(this);
			}
			else
			{
				std::cout << "Teritoriul ales nu este vecin cu niciun teritoriu pe care il detineti sau este printre teritoriile dumneavoastra!" << "\n";
			}
		}
	}
}

void Game::Phase4SelectWinner()
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

void Game::ParseQuestions()
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

void Game::PrintQuestions()
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

Question Game::GetRandomQuestion()
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

QuestionMultipleChoice Game::GetRandomQuestionMultipleChoice()
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

std::vector<Player> Game::GetClasament(Question randomQuestion)
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

void Game::ChooseTerritory(std::vector<Player> clasament)
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

void Game::ChooseBase(std::vector<Player> clasament)
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

int Game::GetCurrentPlayer(Player player)
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

bool Game::IsNeighbours(std::vector<Territory> vector, int linie, int coloana)
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

int Game::FindSecondPlayer(int linie, int coloana)
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

int Game::FindTerritory(int player, int linie, int coloana)
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

int Game::UseAdvantage()
{
	int opt;
	std::cout << "Vrei sa folosesti un avantaj?" << "\n";
	std::cout << "1-pentru Da" << "\n";
	std::cout << "2-pentru Nu" << "\n";
	std::cin >> opt;
	return opt;
}




void Game::on_Generate_clicked()
{
	QString s = "Raspunsul tau:";
	ui->raspuns_jucator->setText(s);
	ui->raspuns_jucator->setVisible(true);
	ui->raspuns1->setVisible(true);
	ui->Submit->setVisible(true);
	ui->Generate->setEnabled(false);
	ui->question->setVisible(true);
}

void Game::on_Submit_clicked()
{
	ui->corect->setVisible(true);
	ui->corect2->setVisible(true);
	ui->diferenta->setVisible(true);
	QString s1 = "Diferenta fata de raspunsul corect: ";
	int diferenta4 = abs(ui->corect2->text().toInt() - ui->raspuns1->text().toInt());
	QString diferenta2 = s1 + QString::number(diferenta4);
	ui->diferenta->setText(diferenta2);
	ui->Submit->setEnabled(false);
}

Game::~Game()
{
    delete ui;
}
