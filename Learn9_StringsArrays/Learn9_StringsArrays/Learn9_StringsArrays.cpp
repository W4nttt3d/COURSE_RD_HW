#include <iostream>

void enterArray(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cin >> array[i];
	}

	//Reset buffer for correct "std::cin.getline" call
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void outputArray(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

//Task 1
void translateArray(int numbers[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] > 0)
		{
			numbers[i] = numbers[i] * 2;
		}
		else if (numbers[i] < 0)
		{
			numbers[i] = 0;
		}

	}
}

//Task 2
void toUppercase(char str[])
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] -= 32;
		}
	}
}

//Task 3
bool isPalindrom(const char str[])
{
	int leftSymbol = 0;
	int rightSymbol = std::strlen(str) - 1;

	while (leftSymbol < rightSymbol)
	{
		if (str[leftSymbol] != str[rightSymbol]) 
		{
			return false;
		}

		leftSymbol++;
		rightSymbol--;
	}

	return true;
}

void parseStringLetters(const char str[], int& vowelsCount, int& constonantsCount)
{
	char vowels[] = "AEIOUYaeiouy";

	vowelsCount = 0;
	constonantsCount = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (std::isalpha(str[i]))
		{
			if (std::strchr(vowels, str[i]))
			{
				vowelsCount++;
			}
			else
			{
				constonantsCount++;
			}
		}
	}
}

bool isEqual(const char str1[], const char str2[])
{
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
		i++;
	}

	if (str1[i] == '\0' && str2[i] == '\0')
	{
		return true;
	}
	else
	{
		return false;
	}
}

constexpr unsigned SIZE_ARRAY_TASK1 = 10;
constexpr unsigned STRING_MAX_SIZE = 25;

int main()
{
	//Task 1
	std::cout << "Enter 10 numbers: "; 
	int numbersForTranslate[SIZE_ARRAY_TASK1] = {};
	enterArray(numbersForTranslate, SIZE_ARRAY_TASK1);
	translateArray(numbersForTranslate, SIZE_ARRAY_TASK1);
	outputArray(numbersForTranslate, SIZE_ARRAY_TASK1);

	std::cout << std::endl;

	//Task 2
	std::cout << "Enter a string: ";
	char stringArray[STRING_MAX_SIZE];
	std::cin.getline(stringArray, STRING_MAX_SIZE - 1);
	toUppercase(stringArray);
	std::cout << stringArray;

	std::cout << std::endl << std::endl;;
	
	//Task 3
	std::cout << "Enter a string: ";
	std::cin.getline(stringArray, STRING_MAX_SIZE - 1);

	if (isPalindrom(stringArray)) 
	{
		std::cout << "The string is a palindrome." << std::endl;
	}
	else 
	{
		std::cout << "The string is not a palindrome." << std::endl;
	}

	std::cout << std::endl;

	//Task 4
	std::cout << "Enter a string: ";
	std::cin.getline(stringArray, STRING_MAX_SIZE - 1);

	int vowelsCount, constonantsCount;
	parseStringLetters(stringArray, vowelsCount, constonantsCount);

	std::cout << "Vowels: " << vowelsCount << std::endl <<
		"Constonants: " << constonantsCount << std::endl;

	std::cout << std::endl;

	//Task 5
	std::cout << "Enter 2 strings: ";

	char stringArray1[STRING_MAX_SIZE];
	std::cin.getline(stringArray, STRING_MAX_SIZE - 1);

	char stringArray2[STRING_MAX_SIZE];
	std::cin.getline(stringArray, STRING_MAX_SIZE - 1);

	if (isEqual(stringArray1, stringArray2))
	{
		std::cout << "The lines are the same";
	}
	else
	{
		std::cout << "The lines are different";
	}

	std::cout << std::endl;
}

