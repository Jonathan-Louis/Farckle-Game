// Farkle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Jonathan Louis
//Farkle Dice Game

#include "Player.h"
#include "Turn.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

	Turn game;

	//reading in text rule file
	ifstream file("FarkleRules.txt");

	string fileLine;

	//getting text from rules file one line at a time
	while (getline(file, fileLine)) {
		cout << fileLine << endl;
	}

	cout << endl << endl;

	game.runGame();
}