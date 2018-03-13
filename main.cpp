#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

void printIntro();
void playGame();
FString getValidGuess();
bool askToPlayAgain();
void printGameSummary();

FBullCowGame bcGame;

int main() {

	bool bPlayAgain = false;
	do {
		printIntro();
		playGame();
		bPlayAgain = askToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void printIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << bcGame.getHiddenWordLength();
	std::cout << " letter isogram I'm thenking of?\n";
	std::cout << std::endl;
	return;
}

void playGame() {
	bcGame.reset();
	int32 maxTries = bcGame.getMaxTries();

	while (!bcGame.isGameWon() && bcGame.getCurrentTry() <= maxTries) {
		FString guess = getValidGuess();

		FBullCowCount bullCowCount = bcGame.submitValidGuess(guess);

		std::cout << "Bulls = " << bullCowCount.Bulls;
		std::cout << ". Cows = " << bullCowCount.Cows << "\n\n";
	}

	printGameSummary();
	return;
}

FString getValidGuess() {
	FString guess = "";
	EGuessStatus status = EGuessStatus::Invalid_status;
	do {
		int32 currentTry = bcGame.getCurrentTry();
		std::cout << "Try " << currentTry << " of " << bcGame.getMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, guess);

		status = bcGame.checkGuessValidity(guess);
		switch (status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << bcGame.getHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// Assuming the guess is valid
			break;
		}
	} while (status != EGuessStatus::OK);
	return guess;
}

bool askToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word (y/n)?";
	FString response = "";
	std::getline(std::cin, response);
	return (response[0] == 'y') || (response[0] == 'Y');
}

void printGameSummary() {

	if (bcGame.isGameWon()) {
		std::cout << "Well done - YOU WIN\n";
	} else {
		std::cout << "Better luck next time!\n";
	}

}
