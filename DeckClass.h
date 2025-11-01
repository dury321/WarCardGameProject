//--------------------------------------------------------------------------------------------------
//File Name:        DeckClass.h
//Associated File:  DeckClass.cpp
//Contains:
//  Constructors:	Default:	deckType
//	Members:					Integer: deckSize
//								cardType: deck[]
//  Access	
//   Get -	(inline)			GetDeckSize
//			(defined in .cpp)	GetCard
//   Set -	(inline)			None
//			(defined in .cpp)	None
//   Print -(inline)			None
//			(defined in .cpp)	PrintTheDeck
//								
// Other Methods -				CreateDeck, Swap, ShuffleTheDeck
// Destructor: 
//			Default:			~deckType
//--------------------------------------------------------------------------------------------------

#pragma once
#include "CardClass.h"

class deckType
{
private:

	//private array of card type with DECK_SIZE to create deck
	cardType deck[DECK_SIZE];

	//tag field for the deck
	int deckSize;

public:

	// --------- Constructor ---------------
	//default constructor
	deckType(void);

	// --------- Public Methods -------------
	//get the card count for the deck
	int GetDeckSize(void) { return deckSize; }

	//get a card from a certain position in the deck
	cardType GetCard(int index);

	//create the deck
	void CreateDeck(cardType deck[]);

	//swap two card objects
	void Swap(cardType& first, cardType& second);

	//randomly swap cards in the deck to shuffle
	void ShuffleTheDeck(void);

	// --------- Print Methods -------------
	//print the deck
	void PrintTheDeck(void);

	// --------- Destructor ----------------
	//default destructor
	~deckType(void);
};