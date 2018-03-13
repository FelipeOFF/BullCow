#pragma once

#include <string>

using int32 = int;
using FString = std::string;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();

	int32 getMaxTries() const; // Retorna o numero maximo de tentativas
	int32 getCurrentTry() const; // Retorna a tentativa atual
	int32 getHiddenWordLength() const; // Retorna a quantidade de letras que tem na palavra escondida
	bool isGameWon() const;  // O Player perdeu?
	EGuessStatus checkGuessValidity(FString) const;

	void reset(); // Reseta o game inteiro
	FBullCowCount submitValidGuess(FString); // Set um isograma valido
private:
	int32 myCurrentTry; // tentativa em progreço
	FString myHiddenWord; // A palavra escondida
	bool bGameIsWon; // o game acabou?

	bool isIsogram(FString) const; // É um isograma?
	bool isLowercase(FString) const; // É um texto lowercase?
};

