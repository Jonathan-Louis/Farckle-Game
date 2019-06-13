#pragma once
#include "Player.h"

//class for each turn
class Turn {
private:
	//establising variables for the game
	Player players[10];
	int dice[6];
	int turnScore, numPlayers, numDice, chosenDice[6], numDiceChosen, scoringDice[6], currentPlayer, diceNumberChosen[6];
	bool turnActive, validPlayerChoice;

	//establishing classes
	void getPlayers();
	void rollDice();
	void choseDice();
	void diceScorer();
	void validChoice();
	void turnScoreLogger();
	void runTurn();

public:
	void runGame();
};