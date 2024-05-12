#include <iostream>
#include <ctime>

char randSymbols()
{
    std::srand(std::time(0));

    const int range = 2;
    const int randNum = std::rand() % (range + 1);
    char randSymbol = 'r';
    switch (randNum)
    {
        case 0:
            randSymbol = 'r';
            break;
        case 1:
            randSymbol = 'p';
            break;
        case 2:
            randSymbol = 's';
            break;
    }
    return randSymbol;
}

char playerSymbol()
{
    std::cout << "\nTo make your turn enter one of possible symbols: \n";
    std::cout << "\t r - rock \t p - paper \t s - scissors\n";

    std::cout << "You choice is ";
    char playerSymbols;
    std::cin >> playerSymbols;
    
    return playerSymbols;
}

void toGame(int roundsNumber, int& numWinsGeneral, int& numLossesGeneral, int& numDrawsGeneral)
{
    int numWins = 0, numLosses = 0, numDraws = 0;
    for (int i = 1; i <= roundsNumber; i++)
    {
        char playerSymbols = playerSymbol();

        while (playerSymbols != 'r' && playerSymbols != 'p' && playerSymbols != 's')
        {
            std::cout << "You entered an incorrect character, please try again\n";
            playerSymbols = playerSymbol();
        }

        char randSymbol = randSymbols();
        std::cout << "PC choice is " << randSymbol << std::endl;

        if (playerSymbols == randSymbol)
        {
            std::cout << "You have a draw(^\n";
            numDraws++;
        }
        else if (playerSymbols == 'r' && randSymbol == 's' || 
            playerSymbols == 'p' && randSymbol == 'r' ||
            playerSymbols == 's' && randSymbol == 'p')
        {
            std::cout << "You WIN(:\n";
            numWins++;
        }
        else
        {
            std::cout << "You LOST):\n";
            numLosses++;
        }

    }
    std::cout << "Thanks for playing. Your stats:" << std::endl;
    std::cout << "\tNumber of rounds - " << roundsNumber << std::endl;
    std::cout << "\tNumber of wins - " << numWins << std::endl;
    std::cout << "\tNumber of losses - " << numLosses << std::endl;
    std::cout << "\tNumber of draws - " << numDraws << std::endl;

    if (numWins > numLosses)
    {
        std::cout << "You WIN\n";
        numWinsGeneral++;
    }
    else if (numWins < numLosses)
    {
        std::cout << "You LOST\n";
        numLossesGeneral++;
    }
    else 
    {
        std::cout << "You have a draw\n";
        numDrawsGeneral++;
    }
}

int enterRounds()
{
    std::cout << "Enter rounds number: \n(-1 to quit) \n(0 to General statistics)\n ";
    int roundsNumber;
    std::cin >> roundsNumber;
    return roundsNumber;
}

void menu()
{
    int numWinsGeneral = 0, numLossesGeneral = 0, numDrawsGeneral = 0, numGamesPlayed = 0;
    while (true)
    {
        int roundsNumber = enterRounds();

        if (roundsNumber == -1)
        {
            break;
        }
        else if (roundsNumber == 0)
        {
            std::cout << "\tNumber of games played - " << numGamesPlayed << std::endl;
            std::cout << "\tNumber of wins - " << numWinsGeneral << std::endl;
            std::cout << "\tNumber of losses - " << numLossesGeneral << std::endl;
            std::cout << "\tNumber of draws - " << numDrawsGeneral << std::endl;
        }
        else if (roundsNumber <= 0)
        {
            std::cout << "The number of rounds cannot be less than 1. Try again.\n";
        }
        else
        {
            toGame(roundsNumber, numWinsGeneral, numLossesGeneral, numDrawsGeneral);
            numGamesPlayed++;
        }
    }
}

int main()
{
    std::cout << "Hello! Welcome to \"Rock paper scissors\"\n";
    menu();
    std::cout << "Thanks for playing";
}