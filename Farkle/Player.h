#pragma once

#include <string>
using namespace std;

//class to store players info

class Player {
private:
	int playerNum;
	string playerName;
	int playerScore = 0;
	bool playerOpen;

public:
	Player() {};

	void setPlayerNum(int i) {
		playerNum = i;
	}

	int getPlayerNum() {
		return playerNum;
	}

	void setPlayerName(string name) {
		playerName = name;
	}

	string getPlayerName() {
		return playerName;
	}

	void setPlayerScore(int score) {
		playerScore = playerScore + score;
	}

	int getPlayerScore() {
		return playerScore;
	}

	void setPlayerOpen(bool open) {
		playerOpen = open;
	}

	bool getPlayerOpen() {
		return playerOpen;
	}
};