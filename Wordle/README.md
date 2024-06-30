Wordle Game Instructions:
	Wordle of the Day: Guess the word chosen for the day and get 10 points. You have a limited number of attempts. 
	Random Wordle: Guess a randomly selected word. You'll be informed if your guess is correct.
	Game Statistics: View the number of games played, games won, games lost, and your total points.
	Exit: Quit the game and save your progress.

How to Play:
	Choose an option from the menu by entering the corresponding number.
	For Wordle of the Day and Random Wordle, enter a word of the correct length to match the hidden word.
	Each correct guess increases your points. Failed attempts count towards your games lost.

Enjoy playing Wordle!

Explanation of the word comparison algorithm:

	1. The user enters their own version of the word.
	2. We check whether the word is suitable for us in length, translate the characters of the word into uppercase
	3. Fill the line in which we will write the user's results with '*', create two dynamic vextor arrays "matched" (if the character is in place), "used" (if the character is used in the word) which have the length of our guessed word.
	4. Check if the characters are in their place
	5. Check if the characters are used in the word
	6. Print the result.
	7. Check if the word entered by the user is correct.

Plans for the future:
	Then you can add a difficulty selection that will change the number of characters in the word.