#include "GameManager.h"
#include "FileIO.h"
#include "DateTime.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>


const unsigned sizeArray = 100;

std::string getRandomWord()
{
    //get an array of words
	std::string listWords[sizeArray];
    readListWords("fiveLetterWords.txt", listWords, sizeArray);

    //random
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::time_t currentTime = std::time(nullptr);

    unsigned randomValue = std::rand() % sizeArray;

    std::string randomWord = listWords[randomValue];
    return randomWord;
}

bool compareWords(std::string randomWord)
{
    std::string enteredWord;
    std::string tempWord(randomWord.length(), '*');

    int attempt = 0;

    while (attempt < randomWord.length())
    {
        std::cout << "\nENTER: ";
        std::cin >> enteredWord;


        if (enteredWord.length() != randomWord.length()) {
            std::cout << "Please enter a word of length " << randomWord.length() << std::endl;
            continue;
        }

        for (int i = 0; i < enteredWord.length(); i++)
        {
            enteredWord[i] = std::toupper(enteredWord[i]);
        }

        tempWord.assign(randomWord.length(), '*');

        std::vector<bool> matched(randomWord.length(), false);
        std::vector<bool> used(randomWord.length(), false);

        for (int i = 0; i < randomWord.length(); ++i) 
        {
            if (randomWord[i] == enteredWord[i]) 
            {
                tempWord[i] = enteredWord[i];
                matched[i] = true;
                used[i] = true;
            }
        }

        for (int i = 0; i < randomWord.length(); ++i) 
        {
            if (!matched[i]) 
            {
                for (int j = 0; j < randomWord.length(); ++j) 
                {
                    if (!used[j] && randomWord[j] == enteredWord[i]) 
                    {
                        tempWord[i] = std::tolower(enteredWord[i]);
                        used[j] = true;
                        break;
                    }
                }
            }
        }

        std::cout << "RESULT: " << tempWord << std::endl;

        if (tempWord == randomWord) {
            return true;
            break;
        }

        attempt++;
    }
    if (tempWord != randomWord) 
    {
        return false;
    }
}

void wordleOfTheDay(int& gamesPlayed, int& gamesWon, int& gamesLost, int& points, std::string& dateTime)
{
    if (getDateTime() != dateTime)
    {
        std::string randomWord = getRandomWord();

        std::cout << randomWord;

        if (compareWords(randomWord))
        {
            std::cout << "Congratulations! You've guessed the word!" << std::endl;
            gamesWon++;
            points =+ 10;
        }
        else
        {
            std::cout << "\nYou didn't guess the word:(. The required word was: " << randomWord;
            gamesLost++;
        }
        dateTime = getDateTime();
        gamesPlayed++;
    }
    else
    {
        std::cout << "You used your attempt to guess the word of the day:(. Come back tomorrow";
    }
}

void randomWordle(int& gamesPlayed, int& gamesWon, int& gamesLost, int& points)
{
    std::string randomWord = getRandomWord();

    std::cout << randomWord;

    if (compareWords(randomWord))
    {
        std::cout << "Congratulations! You've guessed the word!" << std::endl;
        gamesWon++;
        points++;
    }
    else
    {
        std::cout << "\nYou didn't guess the word:(. The required word was: " << randomWord;
        gamesLost++;
    }
    gamesPlayed++;
}

void gameStatistics(int& gamesPlayed, int& gamesWon, int& gamesLost, int& points)
{
    std::cout << "\n---Game Statistics---" << std::endl;
    std::cout << "Games Played: " << gamesPlayed << std::endl;
    std::cout << "Games Won: " << gamesWon << std::endl;
    std::cout << "Games Lost: " << gamesLost << std::endl;
    std::cout << "Points: " << points << std::endl;
}