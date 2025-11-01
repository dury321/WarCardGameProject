//--------------------------------------------------------------------------------------------------
//File Name:        GameClass.h
//Associated File:  GameClass.cpp, StackClass.h
//Contains:
//  Constructors:	Default:	gameType
//	Members:					deckType: deck
//								stackType: pCards, cCards, pTable, cTable, pWinCards, cWinCards
//								Boolean: computerWinner, playerWinner	
//  Access:
//   Get -	(inline)			GetComputerWinner, GetPlayerWinner
//			(defined in .cpp)	None
//   Set -	(inline)			None
//			(defined in .cpp)	None
//   Print -(inline)			None
//			(defined in .cpp)	PrintComputersAndPlayersCards, PrintGameMenu, PrintWarCardsPreWar
//								PrintAndTransferWarCardsResults, PrintWinCardsAndStack
//								
// Other Methods -				StartGame, PlayRound, PushCardsToTable, War, DoubleWarLogic,
//								TransferWinningCardsWithEmptyHands, InGameUserMenu, MenuScreen
// Destructor: 
//			Default:			~gameType
//--------------------------------------------------------------------------------------------------

#pragma once
#include "StackClass.h"

class gameType
{
private:
	//create the deck
	deckType deck;

	//create two stacks for players cards and computer cards
	stackType pCards;
	stackType cCards;

	//create two stacks for the player/computer tables
	stackType pTable;
	stackType cTable;
	
	//create two stacks for the player/computer winning card stacks
	stackType pWinCards;
	stackType cWinCards;

	//boolean values for computer or player as winner
	bool computerWinner;
	bool playerWinner;

public:

	// --------- Constructor ---------------
	//default constructor sets the computer and player winner booleans to false
	gameType(void);

	// --------- Public Methods -------------
	//get functions to return the computer/player winners
	bool GetComputerWinner(void) { return computerWinner; }
	bool GetPlayerWinner(void) { return playerWinner; }

	//start the game by shuffling the deck, and pushing half of the deck to the player and computer's hand
	void StartGame(void);

	//play a game round
	bool PlayRound(bool& playNextRound);
	
	//function to refill card stacks and check whether there are winners
	void PushCardsToTable(bool& continueFlag);

	//play WAR when both player and computer cards are the same
	void War(bool& playNextRound);

	//handle the logic for when double war arises
	void DoubleWarLogic(bool& continueFlag);

	//transfer table cards from both players tables to the computer/player when
	//	hands of computer/player are empty to their respective hands
	void TransferWinningCardsWithEmptyHands(bool computerOrPlayer);

	//handle the logic for when the computer/player run out of cards in hand and in 
	//	their winning stacks
	void EmptyHandAndWinningCardLogic(bool& continueFlag, bool computerOrPlayer);

	//print in game user menu for the user and return the option choice
	int InGameUserMenu(void);

	//print menu for the user, return the menu option choice
	int MenuScreen(void);

	// --------- Print Methods -------------
	//print the computer and players card for WAR
	void PrintComputersAndPlayersCards(void);

	//print greeting game menu for the user
	void PrintGameMenu(void);

	//before war starts, show computer/player cards
	void PrintWarCardsPreWar(void);

	//after winning/losing in WAR
	void PrintAndTransferWarCardsResults(bool computerOrPlayer);

	//print the player/computer winning cards and stack
	void PrintWinCardsAndStack(bool computerOrPlayer);

	// --------- Destructor ----------------
	//default destructor
	~gameType(void);
};

