/* 
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class
*/

#pragma once
#include <iostream>
#include <string>
#include "fBullCowGame.h"
#include <unordered_set>

#define TSet std::unordered_set

//Making code syntax more Unreal friendly
using FText = std::string;
using int32 = int;

//Funtion Prototpes
void PrintIntro();
FText GetValidGuess();
void PlayGame();
void AskDifficulty();
void PrintGameSummary();
bool AskToPlayAgain();

//Global Instances
FBullCowGame BCGame; //instantiate a new game



//Start of Main Function
int main()
{
	bool bPlayAgain = false;
	do{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl << std::endl;
	} 
	while (bPlayAgain);

	return 0; //exit the application
}



// Introducing the game to the player
void PrintIntro()
{
	std::cout << "\n-----------------------------------------------------";
	std::cout << "\nWelcome to the 'Bulls n Cows' word game!";
	std::cout << "\n-----------------------------------------------------\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter Isogram I'm thinking of?\n"; 
	std::cout << "An Isogram is a word with no repeating letters \nGo ahead give it a shot!\n\n";
	std::cout << "*****************************************************\n\n";
}



//Game starts here
void PlayGame()
{
	BCGame.Reset();

	AskDifficulty();
	
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while game is NOT won and there are tries still remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) { 

		FText Guess = GetValidGuess();

		// Submit valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}



//Ask the player for thier preffered difficulty
void AskDifficulty()
{
	FText DifficultyInput = "";

	std::cout << "Choose your difficutly:\n";
	std::cout << "1. Easy Peesy - 3 letter Isogram.\n";
	std::cout << "2. Easy but not too easy...you know what I mean - 4 letter Isogram.\n";
	std::cout << "3. A wee bit difficult - 5 letter Isogram.\n";
	std::cout << "4. Think your good at this?? - 6 letter Isogram.\n";
	std::cout << "5. ''I love torturing my brain'' }:[] - 7 letter Isogram.\n";
	std::cout << "Input the number of your choice of difficulty - ";
	std::getline(std::cin, DifficultyInput);
	
	// Checking for a valid input of difficulty
	const TSet<char> Difficulties = { '1', '2', '3', '4', '5' };
	bool bLoop = false; 
	while (!bLoop) {
		//If the input is valid then call SetDifficulty() and set bLoop true
		if (Difficulties.count(DifficultyInput[0]) != 0) {
			BCGame.SetDifficulty(DifficultyInput[0]);
			bLoop = true;
		}
		//else the loop keeps iterating unitl user gives a valid input
		else {
			std::cout << "Please enter only the number of the difficulty - ";
			std::getline(std::cin, DifficultyInput);
		}
	}

	std::cout << "//----\n\n";
}



// Loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do{
		int32 MyCurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << MyCurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram i.e. a word with no repeating letters\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please type in lowercase alphabets only\n\n";
			break;
		default:
			//assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);  //keep going until we get no errors

	return Guess;
}



//Asking if the player wants to play again
bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Do you want to play again, perhaps with the same or a higher difficulty?(y/n)\n";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}



// Printing the outcome of the game
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "Congratulations!! You guessed right and you WIN!\n"; }
	else { std::cout << "You ran out of tries! Better Luck Next Time!\n"; }
}
