#include "FBullCowGame.h"
#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame() { reset(); }

int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }

int32 FBullCowGame::getMaxTries() const {
	TMap<int32, int32> wordLengthToMaxTries{
		{3, 4},
		{4, 7},
		{5, 10},
		{6, 16},
		{7, 20},
	};
	return wordLengthToMaxTries[myHiddenWord.length()];
}

void FBullCowGame::reset() {
	const FString HIDDEN_WORD = "plane";
	myHiddenWord = HIDDEN_WORD;

	myCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString guess) const {
	if (!isIsogram(guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!isLowercase(guess)) {
		return EGuessStatus::Not_Lowercase;
	} else if (guess.length() != getHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::submitValidGuess(FString guess) {
	myCurrentTry++;
	FBullCowCount bullCowCount;
	int32 wordLength = myHiddenWord.length();

	for (int32 MHWChar = 0; MHWChar < wordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < wordLength; GChar++) {
			if (guess[GChar] == myHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					bullCowCount.Bulls++;
				} else {
					bullCowCount.Cows++;
				}
			}
		}
	}

	if (bullCowCount.Bulls == wordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}
	return bullCowCount;
}

bool FBullCowGame::isIsogram(FString word) const {
	if (word.length() <= 1) { return true; }

	TMap<char, bool> letterSeen;
	for (auto letter : word) {
		letter = tolower(letter);
		if (letterSeen[letter]) {
			return false;
		} else {
			letterSeen[letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::isLowercase(FString word) const {
	for (auto letter : word) {
		if (!islower(letter)) {
			return false;
		}
	}

	return true;
}