#include "FileIO.h"

#include <iostream>
#include <string>
#include <fstream>

void readListWords(const char* fileName, std::string* array, unsigned size)
{
	std::fstream file;
	file.open(fileName, std::ios::in);

	if(!file)
	{
		std::cout << "ERROR READING FILE\n";
		//TODO ERROR
	}
	else
	{
		for (unsigned i = 0; i < size && !file.eof(); i++)
		{
			file >> array[i];
		}
		file.close();
	}
}

void readFile(const char* fileName, int& gamesPlayed, int& gamesWon, int& gamesLost, int& points, std::string& dateTime)
{

	std::fstream file;
	file.open(fileName, std::ios::in);

	if (!file)
	{
		std::cout << "ERROR READING FILE\n";
		//TODO ERROR
	}
	else
	{
		std::string temp;

		file >> temp >> gamesPlayed;
		file >> temp >> gamesWon;
		file >> temp >> gamesLost; 
		file >> temp >> points;

		file.ignore();          

		std::getline(file, temp);  
		dateTime = temp.substr(temp.find(": ") + 2); 

		file.close();
	}
}

void writeFile(const char* fileName, int& gamesPlayed, int& gamesWon, int& gamesLost, int& points, std::string& dateTime)
{

	std::fstream file;
	file.open(fileName, std::ios::out);

	if (!file)
	{
		std::cout << "ERROR WRITING FILE\n";
		//TODO ERROR
	}
	else
	{
		std::string temp;

		file << "gamesPlayed: " << gamesPlayed << "\n";
		file << "gamesWon: " << gamesWon << "\n";
		file << "gamesLost: " << gamesLost << "\n";
		file << "points: " << points << "\n";
		file << "dateTime: " << dateTime << "\n";

		file.close();
	}
}