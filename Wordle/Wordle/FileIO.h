#pragma once

#include <string>
void readListWords(const char* fileName, std::string* array, unsigned size);

void readFile(const char* fileName, int& gamesPlayed, int& gamesWon, int& gamesLost, int& points, std::string& dateTime);

void writeFile(const char* fileName, int& gamesPlayed, int& gamesWon, int& gamesLost, int& points, std::string& dateTime);
