#include "GameManager.h"
#include "FileIO.h"

#include <iostream>

int main()
{
	int gamesPlayed;
	int gamesWon;
	int gamesLost;
	int points;
	std::string dateTime;

	readFile("gameStats.txt", gamesPlayed, gamesWon, gamesLost, points, dateTime);

	while (true)
	{
		std::cout << std::endl <<
			"1 - Wordle of the day\n" <<
			"2 - Random Wordle\n" <<
			"3 - Game statistics\n" <<
			"0 - Exit\n" <<
			"Enter: ";

		short menuItem;
		std::cin >> menuItem;

		switch (menuItem)
		{
		case 0:
			writeFile("gameStats.txt", gamesPlayed, gamesWon, gamesLost, points, dateTime);
			return 0;
		case 1:
			wordleOfTheDay(gamesPlayed, gamesWon, gamesLost, points, dateTime);
			break;
		case 2:
			randomWordle(gamesPlayed, gamesWon, gamesLost, points);
			break;
		case 3:
			gameStatistics(gamesPlayed, gamesWon, gamesLost, points);
			break;
		case 4:
			//TODO
			//Choice of complexity (number of letters in a word)
			break;
		}
	}
}

