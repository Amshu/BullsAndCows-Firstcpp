#include "fBullCowGame.h"
#include <map>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

#define TSet std::unordered_set
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }                 ///Getter Methods
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }  

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }	


//Sets the difficulty of the game by randomly selecting an isogram with the chosen length
void FBullCowGame::SetDifficulty(char num) 
{
	switch (num)
	{
	case '1':
		srand((unsigned int)time(0));
		MyHiddenWord = WordList3[rand() % 10]; 
		break;
	case '2':
		srand((unsigned int)time(0));
		MyHiddenWord = WordList4[rand() % 10];
		break;
	case '3':
		srand((unsigned int)time(0));
		MyHiddenWord = WordList5[rand() % 10];
		break;
	case '4':
		srand((unsigned int)time(0));
		MyHiddenWord = WordList6[rand() % 10];
		break;
	case '5':
		srand((unsigned int)time(0));
		MyHiddenWord = WordList7[rand() % 10];
		break;
	default:
		break;
	}
}



//Getting the maxtries with respect to the difficulty chosen
int32 FBullCowGame::GetMaxTries() const { 
	 TMap<int32, int32> WordLengthToMaxTries = { {3,5} , {4,8} , {5,10} , {6,15} , {7,18} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}



//Called by the constructor
void FBullCowGame::Reset()
{
	const FString RESET_WORD = ""; //preventing magic numbers
	MyHiddenWord = RESET_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}



//Checking if the the guess is a valid input
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess isnt an isogram, return an error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if the guess isnt all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if guess length is wrong 
	{
		return EGuessStatus::Wrong_Length;
	}
	else //otherwise return OK
	{
		return EGuessStatus::OK;
	}
}



//Helper function to check the guess is an isogram
bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat all 0 and 1 letter words as isogram 
	if (Word.length() <= 1) { return true; }
	else{}
	TMap<char, bool> LetterSeen; //define Tmap variable LetterSeen
	//Create a loop to analyze the guess word
	for (auto Letter : Word) {

		Letter = tolower(Letter);
		//check if the letters is already in the dictionary
		if (LetterSeen[Letter]) { return false; }     
		//If not add the letter to the map as true
		else {                               
			LetterSeen[Letter] = true;
		}
	}
	return true;
}



//Helper function to check the guess is in lowercase
bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) { return false; }
	}
	return true;;
}



// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the Hidden Word
	for (int32 i = 0; i < WordLenght; i++) {
		// compare letters against the Guess
		for (int32 j = 0; j < WordLenght; j++) {
			//if they match
			if (MyHiddenWord[i] == Guess[j]) {
				//increment bulls if they're in the same place
				if (i == j) { BullCowCount.Bulls++; }
				//increment cows if not
				else { BullCowCount.Cows++; }
			}
		}
	}
	if (BullCowCount.Bulls == WordLenght) { bGameIsWon = true; }
	else { bGameIsWon = false; }

	return BullCowCount;
}






