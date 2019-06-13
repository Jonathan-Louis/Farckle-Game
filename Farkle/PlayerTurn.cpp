//control actions on players turn

#include "Player.h"
#include "Turn.h"
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

//get intial info for players and initialize each player
void Turn::getPlayers() {
	//get number of players
	cout << "Enter the number of players(10 maximum): \n";
	cin >> numPlayers;

	if (numPlayers < 1 || numPlayers > 10) {
		cout << "Invalid number of players, please select between 1 and 10 players\n\n";
		getPlayers();
	}

	//initialize players for game
	for (int i = 0; i < numPlayers; i++) {
		players[i].setPlayerNum(i + 1);
		players[i].setPlayerScore(0);
		players[i].setPlayerOpen(false);

		string name;

		cout << "Enter Player " << i + 1 << "'s name: \n";
		cin >> name;
		players[i].setPlayerName(name);
	}
}

//rolls the dice randomly between 1 and 6
void Turn::rollDice() {
	srand(time(0));

	cout << "Dice Rolled: \n";

	for (int i = 0; i < numDice; i++)
	{
		dice[i] = (rand() % 6) + 1;
		cout << i + 1 << ". " << dice[i] << endl;
	}

	cout << endl;

	turnActive = false;
	//checking if any scoring dice were rolled, else turn ends
	int scoreCheck[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < numDice; i++) {
		if (dice[i] == 1) {
			turnActive = true;
		}
		else if (dice[i] == 2) {
			scoreCheck[1] = scoreCheck[1] + 1;
		}
		else if (dice[i] == 3) {
			scoreCheck[2] = scoreCheck[2] + 1;
		}
		else if (dice[i] == 4) {
			scoreCheck[3] = scoreCheck[3] + 1;
		}
		else if (dice[i] == 5) {
			turnActive = true;
		}
		else if (dice[i] == 6) {
			scoreCheck[5] = scoreCheck[5] + 1;
		}
	}

	//if no 1's or 5's were rolled checking to see if 3 of any number were rolled
	if (turnActive == false) {
		for (int i = 0; i < 6; i++) {
			if (scoreCheck[i] > 2) {
				turnActive = true;
			}
		}
	}

	//if no 1's, 5's, or 3 of a kind were rolled turn active will be false and the players turn ends.
}

//class for player to select die
void Turn::choseDice() {
	cout << "Enter Die to keep(press enter after each entry, enter 0 after last entry): \n";

	numDiceChosen = 0;

	while (1) {
		int i = 0;

		//break if all die chosen
		if (numDiceChosen == numDice) {
			break;
		}

		cin >> i;

		if (i == 0) {
			break;
		}
		else {
			chosenDice[numDiceChosen] = dice[i - 1];
			diceNumberChosen[numDiceChosen] = i;
		}

		numDiceChosen++;

	}

	//getting number of dice to roll if play continues
	numDice = numDice - numDiceChosen;
}

//adding up score from players selection
void Turn::diceScorer() {
	//reseting score checker
	for (int i = 0; i < 6; i++) {
		scoringDice[i] = 0;
	}

	//adding points for each die chosen
	for (int i = 0; i < numDiceChosen; i++) {
		if (chosenDice[i] == 1) {
			scoringDice[0] = scoringDice[0] + 100;
		}
		else if (chosenDice[i] == 2) {
			scoringDice[1] = scoringDice[1] + 200;
		}
		else if (chosenDice[i] == 3) {
			scoringDice[2] = scoringDice[2] + 300;
		}
		else if (chosenDice[i] == 4) {
			scoringDice[3] = scoringDice[3] + 400;
		}
		else if (chosenDice[i] == 5) {
			scoringDice[4] = scoringDice[4] + 50;
		}
		else if (chosenDice[i] == 6) {
			scoringDice[5] = scoringDice[5] + 600;
		}
	}

	//checking for valid choices
	validChoice();

	if (validPlayerChoice == true) {
		//if chain to check for valid scoring dice
		//checking for 1's
		if (scoringDice[0] == 300) {
			turnScore = turnScore + 1000;
		}
		else if ((scoringDice[0] > 0) && (scoringDice[0] < 300)) {
			turnScore = turnScore + scoringDice[0];
		}
		else if (scoringDice[0] > 300) {
			turnScore = turnScore + 1000 + scoringDice[0] - 300;
		}

		//checking for 2's
		if (scoringDice[1] == 600) {
			turnScore = turnScore + 200;
		}

		//checking for 3's
		if (scoringDice[2] == 900) {
			turnScore = turnScore + 300;
		}

		//checking for 4's
		if (scoringDice[3] == 1200) {
			turnScore = turnScore + 400;
		}

		//checking for 5's
		if (scoringDice[4] == 150) {
			turnScore = turnScore + 500;
		}
		else if ((scoringDice[4] > 0) && (scoringDice[4] < 150)) {
			turnScore = turnScore + scoringDice[4];
		}
		else if (scoringDice[4] > 150) {
			turnScore = turnScore + 500 + scoringDice[4] - 150;
		}

		//checking for 6's
		if (scoringDice[5] == 1800) {
			turnScore = turnScore + 600;
		}
	}
	//if selection was invalid, resets and prompts user for input again
	else {
		cout << "Invalid selection. \n";
		numDice = numDice + numDiceChosen;
		choseDice();
		diceScorer();
	}

}

//checking if valid dice where chosen during selection phase
void Turn::validChoice() {

	validPlayerChoice = true;

	if (numDiceChosen == 0) {
		validPlayerChoice = false;
	}

	if ((scoringDice[1] > 0) && (scoringDice[1] != 600)) {
		validPlayerChoice = false;
	}

	if ((scoringDice[2] > 0) && (scoringDice[2] != 900)) {
		validPlayerChoice = false;
	}

	if ((scoringDice[3] > 0) && (scoringDice[3] != 1200)) {
		validPlayerChoice = false;
	}

	if ((scoringDice[5] > 0) && (scoringDice[5] != 1800)) {
		validPlayerChoice = false;
	}

	//checking if same die was selected more than once
	for (int i = 0; i < numDiceChosen - 1; i++) {
		for (int j = i + 1; j < numDiceChosen; j++) {
			if (diceNumberChosen[i] == diceNumberChosen[j]) {
				validPlayerChoice = false;
			}
		}
	}
}

//Checking if player can end turn and log score
void Turn::turnScoreLogger() {

	if (players[currentPlayer % numPlayers].getPlayerOpen() == true) {
		turnActive = false;
		players[currentPlayer % numPlayers].setPlayerScore(turnScore);
	}
	else if (turnScore > 999) {
		turnActive = false;
		players[currentPlayer % numPlayers].setPlayerScore(turnScore);
		players[currentPlayer % numPlayers].setPlayerOpen(true);
	}
	else {
		cout << "You must score at least 1000 points to open, please continue rolling die.\n";
	}

}

//Master class to run turn
void Turn::runTurn() {

	numDice = 6;
	turnScore = 0;
	int j = 1;
	turnActive = true;


	while (turnActive) {
		rollDice();

		if (turnActive == true) {
			choseDice();
			diceScorer();
		}
		for (int i = 0; i < numDiceChosen; i++) {
			cout << chosenDice[i] << endl;
		}

		cout << numDice << endl;

		cout << turnScore << endl;

		//reseting dice to roll to 6 if all 6 dice scored
		if (numDice == 0) {
			numDice = 6;
		}
		else if (turnActive == false) {
		}
		else {
			cout << "Enter 0 to end your turn and save your turns score or 1 to continue rolling die: \n";
			cin >> j;
			if (j == 0) {
				turnScoreLogger();
			}
		}
	}
}

//Class to run entire game
void Turn::runGame() {
	currentPlayer = 0;
	getPlayers();
	bool gameContinue = true;

	//loop to continue until a player reaches the goal
	while (gameContinue) {
		runTurn();

		cout << "Turn Over \n\n\n";
		cout << players[currentPlayer % numPlayers].getPlayerName() << "'s current total points " << players[currentPlayer % numPlayers].getPlayerScore() << endl;;
		system("pause");

		cout << endl;

		//checking for end of game
		if (players[currentPlayer % numPlayers].getPlayerScore() > 10000) {
			gameContinue = false;
		}

		currentPlayer++;
	}

	//displaying final scores
	cout << "Final Scores: \n";
	for (int i = 0; i < numPlayers; i++) {
		cout << "Player " << players[i].getPlayerName() << " scored " << players[i].getPlayerScore() << " points.\n";
	}
}
