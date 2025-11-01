//--------------------------------------------------------------------------------------------------
//File Name:        DeckClass.cpp
//Associated File:  DeckClass.h
//Contains:
//  Constructors:	Default:	deckType
//  Access:	
//   Get -						GetCard
//   Set -						None
//   Print -					PrintTheDeck
//								
// Other Methods -				CreateDeck, Swap, ShuffleTheDeck
// Destructor: 
//			Default:			~deckType
//--------------------------------------------------------------------------------------------------

#include "DeckClass.h"

/*****************************************************************************************/
/* deckType Default Constructor - This constructor initializes the default values
* for the deck class type and creates a deck (in order). It sets the initial deck size to 0.
******************************************************************************************/
deckType::deckType(void)
{
	//object creation counter
	static int counter = 0;

	//echo prompt -- uncomment to see initializations of objects -- uncomment to see object creation
	//cout << "Deck Class Object # " << ++counter << " created. " << endl;

	//set the tag field for the deck to 0 before creating the deck
	deckSize = 0;

	//create the deck in the constructor
	CreateDeck(deck);

}

/*****************************************************************************************/
/* deckType GetCard - Return a card within the deck. Check the bounds of the card by sending
* in the index of the card in the deck you are looking for. Pass into the function the index
* of the card that you are looking for. 
******************************************************************************************/
cardType deckType::GetCard(int index)
{
	//check to make sure the index is within the bounds of the deck by using the tag field
	//	for the deck
	if (index >= 0 && index < GetDeckSize())
	{
		//return the card at that position in the deck
		return deck[index];
	}
	else
	{
		//throw an exception if access outside of the range is attempted
		throw out_of_range("Index out of range.");
	}
}

/*****************************************************************************************/
/* deckType CreateDeck - This function passes in the array of cards and creates a deck of 
* 52 cards with the cardType. Assign suits and rank so that there are 14 of each suit, and 
* each suit has one of each rank. Increase the tag field for the deck size that is created.
******************************************************************************************/
void deckType::CreateDeck(cardType deck[])
{
	//indexes and card and suit starter values
	int index;
	int card = 2;
	int suit = heart;

	//loop through entire array of structures to create your deck of 52 cards
	for (index = 0; index < DECK_SIZE; index++)
	{
		//assign a rank and a suit
		deck[index].SetRank(card); // = card;
		deck[index].SetSuit(suit); // = suit;

		//increase card counter
		card++;
		
		//increase tag field for the deck
		deckSize++;

		//check to see if you got to the highest card value -- if so, reset and start again
		if (card == 15)
		{
			//reset card counter
			card = 2;
			//increase suit
			suit++;
		}
	}
}

/*****************************************************************************************/
/* deckType PrintTheDeck - This function prints the deck consisting of 52 cards to the screen. 
	For every 14 cards there is a new line. 
******************************************************************************************/
void deckType::PrintTheDeck(void)
{
	//index and 
	int index;
	int card = 1;
	int suitChange = 1;

	//loop through to print the deck of 52 cards
	for (index = 0; index < DECK_SIZE; index++)
	{
		//print the card based on the index -- include rank and suit
		deck[index].PrintACard(cout);

		//increase the suit by 1
		suitChange++;

		//reset suit change back to one if you have hit the highest rank -- the King
		if (suitChange == 14)
		{
			//reset the suit change
			suitChange = 1;

			//new line
			cout << endl;
		}
	}
}

/*****************************************************************************************/
/* deckType Swap - This function will swap all members of two different cardType structures
* that are passed into the function. 
******************************************************************************************/
void deckType::Swap(cardType& first, cardType& second)
{
	//create temporary card structure
	cardType temp;

	//swap between two structures using a temporary structure as a middle man
	temp = first;
	first = second;
	second = temp;
}


/*****************************************************************************************/
/* deckType ShuffleTheDeck - This function shuffles the deck of 52 cards in a random method using
*					the current time to seed the shuffling. It swaps the deck in some random
*					position based on the time. 
******************************************************************************************/
void deckType::ShuffleTheDeck(void)
{
	//index and random spot tag
	int randSpot;
	int index;

	//seed the random function with the clock time
	srand(unsigned int(time(NULL)));

	/// We go through the whole deck
	for (index = 0; index < DECK_SIZE; index++)
	{
		/// rand function will give you a random number between 0 and the max integer.  The % with deck size
		/// give you a random number between 0 and one less than that number.
		randSpot = rand() % DECK_SIZE;

		/// We then swap the card sport we are on (index) with the random spot
		Swap(deck[index], deck[randSpot]);
	}
}

/*****************************************************************************************/
/* deckType Default Destructor - This destructor destroys the deck class type
* and prints a message to the screen. 
******************************************************************************************/
deckType::~deckType(void)
{
	//accumulator counter
	static int counter = 0;

	//echo prompt -- uncomment to see destructions of objects
	//cout << "Deck Class Object # " << ++counter << " destroyed. " << endl;
}