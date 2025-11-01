//--------------------------------------------------------------------------------------------------
//File Name:        CardType.h
//Associated File:  CardType.cpp
//Contains:
//  Constructors:	Default:	cardType
//	Members:					Integer: rank, suit
//  Access	
//   Get -	(inline)			GetRank, GetSuit
//			(defined in .cpp)	None
//   Set -	(inline)			SetRank, SetSuit
//			(defined in .cpp)	None
//   Print -(inline)			None
//			(defined in .cpp)	Overloaded: PrintACard
//								
// Other Methods -				Overloaded: operator==, operator<, operator>
//								Overloaded (friend): operator<<
// Destructor: 
//			Default:			~cardType
//--------------------------------------------------------------------------------------------------

#pragma once
#include "OutputClass.h"

class cardType
{
private: 

	//private variables for the card -- rank and suit (suit is enum type)
	int rank;
	int suit;

public:

	// --------- Constructor ---------------
	//default constructor
	cardType(void);

	// --------- Public Methods -------------
	//Get rank and suit methods
	int GetRank(void) { return rank; }
	int GetSuit(void) { return suit; }

	//Set rank and suit methods
	void SetRank(int newRank) { rank = newRank; }
	void SetSuit(int newSuit) { suit = newSuit; }

	//overload the '==' operator to test if two cards are the same
	bool operator==(const cardType& otherCard);

	//overload the '<' less than operator for two cards
	bool operator<(const cardType& otherCard);
	//overload the '>' greater than operator for two cards
	bool operator>(const cardType& otherCard);

	//overload the '<<' extraction operator to print a card to the ostream
	friend ostream& operator<<(ostream& os, const cardType& card);

	// --------- Print Methods -------------
	// print a card -- make constant so that the card object cannot be 
	//		manipulated -- allows use in the overloaded '<<' operator
	void PrintACard(ostream& os) const;
	void PrintACard(int suit, int rank);

	// --------- Destructor ----------------
	//default destructor
	~cardType(void);
};

