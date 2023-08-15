#pragma once
#include <string>
#include "Profile.h"
#include "Territory.h"
#include "Advantages.h"
#include "QuestionMultipleChoice.h"
class Player
{
public:
	Player() = default;
	Player(const std::string& username, const std::string& password, const Profile& profile, const Advantages& advantages);
	Player(const Player& player);

	const std::string& GetUsername() const;
	const std::string& GetPassword() const;
	const Profile& GetProfile() const;
	const Advantages& GetAdvantages() const;
	std::vector<Territory> GetTerritories() const;

	void SetTerritories(Territory territory);
	void UnsetTerritories(int numar);
	void ReplaceTerritory(int numar, Territory teritoriu);

	bool IsUnique(const std::string& newUsername);
	void ChooseAdvantage(QuestionMultipleChoice question);
	void SuggestAnswer(QuestionMultipleChoice question);
	void ChooseAnswer(Question question);
	void RemoveHalfOfAnswers(QuestionMultipleChoice question);

	friend std::ostream& operator<<(std::ostream& out, const Player& player);

	virtual ~Player()=default;
protected:
	std::string m_username;
	std::string m_password;
	Profile m_profile;
	std::vector<Territory> m_territories;   //referinta
	Advantages m_advantages;
};

