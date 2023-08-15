#include "lobby.h"
#include "ui_lobby.h"

Lobby::Lobby(std::string username,QWidget* parent) :
	QDialog(parent),
	ui(new Ui::Lobby)

{
	ui->setupUi(this);
	ui->NewLobbyNumberPlayers->setMinimum(2);
	ui->NewLobbyNumberPlayers->setMaximum(4);
	m_username = username;
	connect(ui->ListLobbyW, &QListWidget::itemClicked, this, &Lobby::on_ListLobbyW_itemClicked);

}

Lobby::~Lobby()
{
	delete ui;
}


std::vector<Player> Lobby::GetPlayers(int index)
{
	return m_Lobbys[index];
}

void Lobby::AddLobby(Player host)
{
	m_Lobbys.push_back(std::vector<Player>{host});
}

//void Lobby::on_AddLobby_clicked()
//{
//    if (ui->NewNameLobby->text()=="")
//    {
//        QMessageBox::critical(this, "Can't add", "The visitor name is not filled in.", QMessageBox::Button::Ok); // modal window
//        return;
//    }
//    /*std::string aux;
//    aux = ui->NewNameLobby->text().toStdString()+"  :"+ui->NewLobbyNumberPlayers->text().toStdString();
//    ui->ListLobbyW->addItem(QString::fromStdString(aux));
//    ui->NewNameLobby->clear();
//    */
//    //Add in vector playeri
//    std::string roomName = ui->NewNameLobby->text().toUtf8().constData();
//    int no_players = ui->NewLobbyNumberPlayers->text().toInt();
//    cpr::Response response = cpr::Post(cpr::Url{"http://localhost:18080/create_room/" + roomName + "/" + std::to_string(no_players)});
//    if (response.status_code == 200) {
//        QMessageBox::information(this, "Room created", "Thanks!", QMessageBox::Button::Ok); // modal window
//        return;
//    }
//    else {
//        QMessageBox::information(this, "Error", "Failed", QMessageBox::Button::Ok); // modal window
//        return;
//    }
//    ui->ListLobbyW->setEnabled(false);
//
//
//}

void Lobby::on_AddLobby_clicked()
{
	if (ui->NewNameLobby->text() == "")
	{

		QMessageBox::critical(this, "Can't add", "The visitor name is not filled in.", QMessageBox::Button::Ok); // modal window
		return;
	}
	std::string roomName = ui->NewNameLobby->text().toUtf8().constData();
	int noPlayers = ui->NewLobbyNumberPlayers->text().toInt();
	std::string creator = m_username;
	crow::json::wvalue body = { {"room_name", roomName}, {"max_players", noPlayers},{"username", creator} };
	auto response = cpr::Post(
		cpr::Url{ "http://localhost:18080/create_room" },
		cpr::Body{ body.dump() }
	);
	if (response.status_code == 200) {
		QMessageBox::information(this, "Room created", "Thanks!", QMessageBox::Button::Ok); // modal window
		return;
	}
	else {
		QMessageBox::information(this, "Error", "Failed", QMessageBox::Button::Ok); // modal window
		return;
	}
	ui->ListLobbyW->setEnabled(false);

}

void Lobby::on_ListLobbyW_itemClicked(QListWidgetItem* item)
{
	ui->ListLobbyW->setCurrentItem(item);
}

void Lobby::on_ListLobbyW_itemChanged(QListWidgetItem* item)
{
	std::cout << ui->ListLobbyW->indexFromItem(item).row();

	//after we stock the list of server add funtion to write players
}

void Lobby::on_refresh_clicked()
{
	ui->ListLobbyW->clear();
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/list_rooms" });
	std::string json_string = response.text;
	size_t name_pos = json_string.find("\"name\":\"");
	while (name_pos != std::string::npos) {
		size_t end_name_pos = json_string.find("\",\"", name_pos);
		std::string room_name = json_string.substr(name_pos + 8, end_name_pos - (name_pos + 8));
		size_t max_players_pos = json_string.find("\"max players\":", end_name_pos);
		size_t end_max_players_pos = json_string.find(",", max_players_pos);
		int max_players = std::stoi(json_string.substr(max_players_pos + 14, end_max_players_pos - (max_players_pos + 14)));
		// Do something with the room_name and max_players here
		QString temp = (room_name.c_str());
		QString room_string = temp + " (" + QString::number(max_players) + " players)";
		QListWidgetItem* item = new QListWidgetItem(room_string);
		ui->ListLobbyW->addItem(item);
		name_pos = json_string.find("\"name\":\"", end_max_players_pos);
	}
}
std::vector<std::string> split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}
void Lobby::on_show_clicked()
{
	QListWidgetItem* selected_item = ui->ListLobbyW->currentItem();
	std::string room_text = selected_item->text().toUtf8().constData();
	std::string room_name = room_text.substr(0, room_text.find("("));
	room_name.pop_back();
	// Make a GET request to the server to get the players in the room
	auto response = cpr::Get(cpr::Url{ "http://localhost:18080/players_in_room/" + room_name });

	if (response.status_code == 200) {
		// Clear the ListPlayersW widget
		ui->ListPlayersW->clear();

		// Split the players list by ',' and add each player to the ListPlayersW widget
		std::string players_list = response.text;
		std::vector<std::string> players = split(players_list, ',');
		for (auto player : players) {
			QString temp = (player.c_str());
			QListWidgetItem* item = new QListWidgetItem(temp);
			ui->ListPlayersW->addItem(item);
		}
	}
	else {
		QMessageBox::information(this, "Error", "Failed to get players in room", QMessageBox::Button::Ok);
	}
}



void Lobby::on_pushButton_2_clicked()
{
	// Get the selected item from the list widget
	QListWidgetItem* selected_item = ui->ListLobbyW->currentItem();
	if (selected_item == nullptr) {
		// No item was selected, show an error message
		QMessageBox::warning(this, "Error", "Please select a room to join.");
		return;
	}
	std::string joiner = m_username;
	// Extract the room name from the text of the selected item
	std::string room_text = selected_item->text().toUtf8().constData();
	std::string room_name = room_text.substr(0, room_text.find("("));
	//QString room_name = selected_item->text().toUtf8().constData();;
	//std::string roomName = selected_item->text().toUtf8().constData();
	// Send a request to the server to join the room
	room_name.pop_back();
	std::string requestBody = "{\"room_name\":\"" + room_name + "\",\"username\":\"" + joiner + "\"}";
	cpr::Response response = cpr::Post(cpr::Url{ "http://localhost:18080/join_room" }, cpr::Body{ requestBody });
	if (response.status_code != 200) {
		// Show an error message if the request was not successful
		QMessageBox::warning(this, "Error", "Failed", QMessageBox::Button::Ok);
	}
	else {
		// Show a message if the join was successful
		QMessageBox::information(this, "Success", "Successfully joined room.");
	}
}

void Lobby::on_pushButton_3_clicked()
{
	m_game = new Game;
	m_game->setModal(true);
	m_game->show();
	this->close();
}


