/* 
The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on mastermind
*/

#pragma once
#include <string>

//Making code syntax more Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};


class FBullCowGame {
public:
	FBullCowGame(); //Constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	void SetDifficulty(char);

	EGuessStatus CheckGuessValidity(FString) const; 
	bool IsGameWon() const;

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);
	
private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	 
	//Arrays containing the respective length isograms
	FString WordList3[10] = { "arm", "tap", "pin", "fog", "cut", "gas", "wed", "rob", "boa", "ore" };
	FString WordList4[10] = { "fire", "blue", "army", "gram", "mars", "rags", "xray", "calm", "game", "duck" };
	FString WordList5[10] = { "organ", "piano", "gravy", "zebra", "aisle", "vocal", "waste", "stand", "raise", "quiet" };
	FString WordList6[10] = { "bandit", "carpet", "damsel", "garlic", "hacker", "magpie", "pencil", "rasicm", "tackle", "zombie" };
	FString WordList7[10] = { "airport", "defrost", "glacier", "include", "justify", "knights", "qualify", "racquet", "sharpen", "urgency" };

	bool IsIsogram(FString) const; //private functions are called helper functions
	bool IsLowercase(FString) const;
};
