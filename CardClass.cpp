//--------------------------------------------------------------------------------------------------
//File Name:        CardType.cpp
//Associated File:  CardType.h
//Contains:
//  Constructors:	Default:	cardType
//  Access:			
//   Get -						None				
//   Set -						None
//   Print -					Overloaded: PrintACard
//								
// Other Methods -				Overloaded: operator==, operator<, operator>
//								Overloaded (friend): operator<<
// Destructor: 
//			Default:			~cardType
//--------------------------------------------------------------------------------------------------

#include "CardClass.h"

/*****************************************************************************************/
/* cardType Default Constructor - This constructor initializes the default values
* for the card class type.
******************************************************************************************/
cardType::cardType(void)
{
	//object creation counter
	static int counter = 0;

	//echo prompt -- uncomment to see initializations of objects -- uncomment to see object creation
	//cout << "Card Class Object # " << ++counter << " created. " << endl;

	//initialize member variables
	rank = 0;
	suit = 0;
}

/*****************************************************************************************/
/* cardType PrintACard - This function prints out to the screen an individual card with its rank 
				and suit. The output stream is passed in to the function. The function checks the
				rank of the card to see if it is a face card, and if so, prints the appropriate
				symbol to the output stream.
******************************************************************************************/
void cardType::PrintACard(ostream& os) const
{
	//print character for face cards
	char printChar;

	if (rank >= 2 && rank <= 10)
	{
		// WINDOWS 11 Unicode Problems
		// Cannot print suit symbols on WIN 11 -- tried every font (raster and otherwise), every text width, font size, opening different
		// profiles, trying with and without a text renderer, trying it on my laptop, resetting my terminal .JSON settings file, 
		// resetting my VStudio, restarting my computer and laptop, enlisting the help of the Internet and friends...
		// This is the only work around that I found. Code without this segment prints out on WIN 10, but not on WIN 11...
		// I put it in a switch statement to keep with the theme even if it is an extraneous piece of code...
		// CODE THAT WORKS ON WIN 10
		//		if (card >= 2 && card <= 10)
		//		{
		//			cout << setw(5) << card << char(suit);			//cast the integer to a character for printing suit symbol
		// 
		//												...
		// 
		//			cout << setw(5) << printChar << (char)suit;		//cast the integer to a character and print face symbol
		//		}

		// WIN 11 WORK AROUND ------------------------------------------------
		switch (suit)
		{
		case 3:
			os << setw(5) << rank << "\u2660";	//print heart suit symbol
			break;
		case 4:
			os << setw(5) << rank << "\u2666";	//print diamond suit symbol
			break;
		case 5:
			os << setw(5) << rank << "\u2663";	//print club suit symbol	
			break;
		default:
			os << setw(5) << rank << "\u2660";	//print spade suit symbol
		}
		//--------------------------------------------------------------------
	}
	else
	{
		//print face cards
		switch (rank)
		{
		case 11:
			printChar = 'J';	//print Jack
			break;
		case 12:
			printChar = 'Q';	//print Queen
			break;
		case 13:
			printChar = 'K';	//print King
			break;
		default:
			printChar = 'A';	//print Ace
		}

		// WIN 11 WORK AROUND ------------------------------------------------
		switch (suit)
		{
		case 3:
			os << setw(5) << printChar << "\u2660";	//print heart suit symbol
			break;
		case 4:
			os << setw(5) << printChar << "\u2666";	//print diamond suit symbol
			break;
		case 5:
			os << setw(5) << printChar << "\u2663";	//print club suit symbol	
			break;
		default:
			os << setw(5) << printChar << "\u2660";	//print spade suit symbol
		}
		//--------------------------------------------------------------------
	}
}

/*****************************************************************************************/
/* cardType PrintACard - This function prints out to the screen an individual card with its 
				rank and suit. The cards rank and suit are passed into the function. The 
				function checks the rank of the card to see if it is a face card, and if so, 
				prints the appropriate symbol.
******************************************************************************************/
void cardType::PrintACard(int rank, int suit) 
{
	//print character for face cards
	char printChar;

	if (rank >= 2 && rank <= 10)
	{
		// WINDOWS 11 Unicode Problems
		// Cannot print suit symbols on WIN 11 -- tried every font (raster and otherwise), every text width, font size, opening different
		// profiles, trying with and without a text renderer, trying it on my laptop, resetting my terminal .JSON settings file, 
		// resetting my VStudio, restarting my computer and laptop, enlisting the help of the Internet and friends...
		// This is the only work around that I found. Code without this segment prints out on WIN 10, but not on WIN 11...
		// I put it in a switch statement to keep with the theme even if it is an extraneous piece of code...
		// CODE THAT WORKS ON WIN 10
		//		if (card >= 2 && card <= 10)
		//		{
		//			cout << setw(5) << card << char(suit);			//cast the integer to a character for printing suit symbol
		// 
		//												...
		// 
		//			cout << setw(5) << printChar << (char)suit;		//cast the integer to a character and print face symbol
		//		}

		// WIN 11 WORK AROUND ------------------------------------------------
		switch (suit)
		{
		case 3:
			cout << setw(2) << rank << "\u2660";	//print heart suit symbol
			break;
		case 4:
			cout << setw(2) << rank << "\u2666";	//print diamond suit symbol
			break;
		case 5:
			cout << setw(2) << rank << "\u2663";	//print club suit symbol	
			break;
		default:
			cout << setw(2) << rank << "\u2660";	//print spade suit symbol
		}
		//--------------------------------------------------------------------
	}
	else
	{
		//print face cards
		switch (rank)
		{
		case 11:
			printChar = 'J';	//print Jack
			break;
		case 12:
			printChar = 'Q';	//print Queen
			break;
		case 13:
			printChar = 'K';	//print King
			break;
		case 14:
			printChar = 'A';	//print Ace
		default:
			printChar = '?';	//print error symbol
		}

		// WIN 11 WORK AROUND ------------------------------------------------
		switch (suit)
		{
		case 3:
			cout << setw(2) << printChar << "\u2660";	//print heart suit symbol
			break;
		case 4:
			cout << setw(2) << printChar << "\u2666";	//print diamond suit symbol
			break;
		case 5:
			cout << setw(2) << printChar << "\u2663";	//print club suit symbol	
			break;
		default:
			cout << setw(2) << printChar << "\u2660";	//print spade suit symbol
		}
		//--------------------------------------------------------------------
	}
}

/*****************************************************************************************/
/* cardType operator== - Overload the '==' operator to check whether two cards are the same.
* Send in the other card, and check the ranks of each card. Return a boolean true/false flag
* depending on the ranks of the card, and return this flag. 
******************************************************************************************/
bool cardType::operator==(const cardType& otherCard)
{
	//create boolean comparator
	bool isEqual;

	//initialize comparator to false
	isEqual = false;

	//test to see if the ranks are equal
	if (rank == otherCard.rank)
	{
		//if they are the same, set the equality comparator to true
		isEqual = true;
	}

	//if they are not, the dates are not equal 
	return isEqual;
}

/*****************************************************************************************/
/* cardType operator< - Overload the '<' operator to check whether one card is less than 
* the other by testing on the rank. Aces are high. Send in the other card to the function
* and compare the ranks. Return a boolean true/false flag for the relational operation. 
******************************************************************************************/
bool cardType::operator<(const cardType& otherCard)
{
	//create boolean comparator
	bool lessThan;

	//initialize comparator to false
	lessThan = false;

	//test to see if the ranks are equal
	if (rank < otherCard.rank)
	{
		//if they are the same, set the equality comparator to true
		lessThan = true;
	}

	//if they are not, the dates are not equal 
	return lessThan;
}

/*****************************************************************************************/
/* cardType operator> - Overload the '>' operator to check whether one card is greater than
* the other by testing on the rank. Aces are high. Send in the other card to the function
* and compare the ranks. Return a boolean true/false flag for the relational operation. 
******************************************************************************************/
bool cardType::operator>(const cardType& otherCard)
{
	//create boolean comparator
	bool greaterThan;

	//initialize comparator to false
	greaterThan = false;

	//test to see if the ranks are equal
	if (rank > otherCard.rank)
	{
		//if they are the same, set the equality comparator to true
		greaterThan = true;
	}

	//if they are not, the dates are not equal 
	return greaterThan;
}

/*****************************************************************************************/
/* cardType operator<< - Overload the '<<' operator to output a card to the ostream. This
* function takes in the ostream, along with the card type object. The function calls
* PrintACard to the ostream sent in to print the card with the associated rank and suit to 
* the ostream.
******************************************************************************************/
ostream& operator<<(ostream& os, const cardType& card)
{
	//use the print card function to print the card
	card.PrintACard(os);

	//return the stream
	return os;
}

/*****************************************************************************************/
/* cardType Default Destructor - This destructor destroys the card class type
* and prints a message to the screen. 
******************************************************************************************/
cardType::~cardType(void)
{
	//accumulator counter
	static int counter = 0;

	//echo prompt -- uncomment to see destructions of objects
	//cout << "Card Class Object # " << ++counter << " destroyed. " << endl;
}