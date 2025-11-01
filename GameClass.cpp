//--------------------------------------------------------------------------------------------------
//File Name:        GameClass.h
//Associated File:  GameClass.cpp, StackClass.h
//Contains:
//  Constructors:	Default:	gameType
//  Access:	
//   Get -						None
//   Set -						None
//   Print -					PrintComputersAndPlayersCards, PrintGameMenu, PrintWarCardsPreWar
//								PrintAndTransferWarCardsResults, PrintWinCardsAndStack
//								
// Other Methods -				StartGame, PlayRound, PushCardsToTable, War, DoubleWarLogic,
//								TransferWinningCardsWithEmptyHands, InGameUserMenu, MenuScreen
// Destructor: 
//			Default:			~gameType
//--------------------------------------------------------------------------------------------------

#include "GameClass.h"

/*****************************************************************************************/
/* gameType Default Constructor - The game type class default constructor initializes the 
* boolean values for the computer/player winning variables. 
******************************************************************************************/
gameType::gameType(void)
{
	//object creation counter
	static int counter = 0;

	//echo prompt -- uncomment to see initializations of objects -- uncomment to see object creation
	//cout << "Game Class Object # " << ++counter << " created. " << endl;
	
	//set computer and player winner boolean values to false
	computerWinner = false;
	playerWinner = false;
}

/*****************************************************************************************/
/* gameType StartGame - This function takes the deck object with 52 card objects and shuffles
* it randomly. Then, the deck is split between the player and user evenly, so they both
* have 26 cards in their hand to start. 
******************************************************************************************/
void gameType::StartGame(void)
{
	//index for dividing the deck in half between player/computer
	int index;

	//after creation of the deck, shuffle it
	deck.ShuffleTheDeck();

	//iterate through the deck based on the deck size to evenly distribute the cards
	for (index = 0; index < deck.GetDeckSize(); index++)
	{
		//allocate the cards for the computer and the user based on even and oddness
		//	give every other card to the user/computer to divide the deck by 2
		if (index % 2 == 0)
		{
			//give the player the cards in their hand
			pCards.Push(deck.GetCard(index));
		}
		else
		{
			//give the computer the cards in their hand
			cCards.Push(deck.GetCard(index));
		}
	}
}
/*****************************************************************************************/
/* gameType PrintGameMenu - This function prints a game menu for the user with the game
* logo. 
******************************************************************************************/
void gameType::PrintGameMenu(void)
{
	//clear the terminal screen
	system("cls");

	//print the game title to the user
	cout << setw((SCREEN_SIZE + GAME_TITLE.length()) / 2) << GAME_TITLE << endl;

	//output menu for user
	cout << " <================= Menu ====================> "
		<< endl;
	cout << "    (1) Start Game " << endl;	// prompts for user to choose choice to start game
	cout << "    (2) End Game " << endl;	// prompt for user to end game
	cout << " <===========================================> "
		<< endl;
	cout << " -> ";	//user selection arrow
}

/*****************************************************************************************/
/* gameType MenuScreen - This function prints a game menu for the user using PrintGameMenu,
* and handles the input selection logic for the user. It preforms error checking to make
* sure that the user inputs a correct input for the start of the game menu. The function
* then returns the user's selection.
******************************************************************************************/
int gameType::MenuScreen(void)
{
	//variable for the user's selection in the game menu
	int userSelection;

	//initialize the deck selection to 0
	userSelection = 0;
	
	//print the game menu to the screen
	PrintGameMenu();

	//get user input for menu selection
	cin >> userSelection;

	//error checking the user's input... make sure they make a correct selection
	while (userSelection != 1 && userSelection != 2)
	{
		//print error message if they do not put in a correct selection
		cout << endl << "Error: Please input correct (1) or (2) selection from menu. " << endl;

		//get user's selection again
		cin >> userSelection;
	}

	//return the user's choice
	return userSelection;
}

/*****************************************************************************************/
/* gameType EmptyHandAndWinningCardLogic - This function handles the game logic when either
* the player or the computer runs out of cards in their hand, and in their winning card stack.
* While there are at least two cards on the table (to handle the logic where one player/computer
* was able to push a card and the other was not due to an empty hand) compare them and decide
* a winner. Push all winning cards to the computer/player. If there is a tie, give the
* advantage to the underdog (the one about to lose). If there is no cards on one or both the
* tables, give the automatic win to the player/computer with cards that are remaining. Two
* variables, the boolean continueFlag that is passed by reference determines if play continues,
* and the boolean computerOrPlayer to choose whose logic to handle when one or the other 
* runs out of cards. 
******************************************************************************************/
void gameType::EmptyHandAndWinningCardLogic(bool& continueFlag, bool computerOrPlayer)
{
	//if computer runs out of cards in hand and in their winning stack
	if (computerOrPlayer)
	{
		//check to make sure that the table top does not have any cards for the player/computer
		//	if they are NULL, then the player is automatically set as the winner and no further 
		//	rounds are played
		if (cTable.GetTop() != NULL && pTable.GetTop() != NULL)
		{
			//divider from game title
			OutputDivider((ofstream&)cout, '=', SCREEN_SIZE);

			//show prompt for user that the computer ran out of cards
			cout << endl << "Computer ran out of cards. ";
			//show user that there will be a sudden final death comparing last cards on the table
			cout << endl << "Final Card Comparison with Sudden Death (tie breaker advantage to the underdog... the computer!): " << endl;
			//show the computer's card from the table and the player card
			cout << "Computer's Card: " << cTable.GetTop()->dataCard << endl << "Player's Card: " << pTable.GetTop()->dataCard << endl;

			//divider from game title
			OutputDivider((ofstream&)cout, '=', SCREEN_SIZE);

			//compare the players top card on the table and the computers
			if (pTable.GetTop()->dataCard > cTable.GetTop()->dataCard)
			{
				//echo prompt that user wins
				cout << endl << "Player Wins!" << endl;

				//set the boolean flag that the player won
				playerWinner = true;
				//set the continue playing rounds flag to false
				continueFlag = false;

				//transfer winning cards to player (handles extraneous card pickup)
				TransferWinningCardsWithEmptyHands(true);
			}
			//if the computer wins or the cards are equal (there is an underdog advantage to the computer who is about to lose),
			//	then continue playing the game
			else
			{
				//if the cards are the same... give advantage to underdog
				if (pTable.GetTop()->dataCard == cTable.GetTop()->dataCard)
				{
					//echo prompt that the computer wins because cards are equal
					cout << endl << "Cards are equal... Advantage and win to computer! Transferring winning cards..." << endl;
				}
				else
				{
					//echo prompt that the computer wins
					cout << endl << "Computer Wins! Transferring winning cards..." << endl;
				}
				
				//transfer winning cards to computer
				TransferWinningCardsWithEmptyHands(false);

				//computer is still in the game, so push one card to the table so comparisons can continue
				cTable.Push(cCards.Pop());

				//set the continue flag to false
				continueFlag = true;
			}
		}
		//if there is no cards on one or both tables, then automatically set the player to win and do not continue
		else
		{
			//set the boolean flag that the player won
			playerWinner = true;
			//set the continue playing rounds flag to false
			continueFlag = false;
		}
	}
	//if player runs out of cards in hand and in their winning stack
	else
	{
		//check to make sure that the table top does not have any cards for the player/computer
		//	if they are NULL, then the player is automatically set as the winner and no further 
		//	rounds are played
		if (cTable.GetTop() != NULL && pTable.GetTop() != NULL)
		{
			//divider from game title
			OutputDivider((ofstream&)cout, '=', SCREEN_SIZE);

			//show prompt for user that the Player ran out of cards
			cout << endl << "Player ran out of cards. ";
			//show user that there will be a sudden final death comparing last cards on the table
			cout << endl << "Final Card Comparison with Sudden Death (tie breaker advantage to the underdog... the player!): " << endl;
			//show the computer's card from the table and the player card
			cout << "Computer's Card: " << cTable.GetTop()->dataCard << endl << "Player's Card: " << pTable.GetTop()->dataCard << endl;

			//divider from game title
			OutputDivider((ofstream&)cout, '=', SCREEN_SIZE);

			//compare the players top card on the table and the computers
			if (cTable.GetTop()->dataCard > pTable.GetTop()->dataCard)
			{
				//echo prompt that computer wins
				cout << endl << "Computer Wins!" << endl;
				//set the continue playing rounds flag to false
				continueFlag = false;

				//set the boolean value that the computer has won
				computerWinner = true;

				//transfer winning cards to computer (handles extraneous card pickup)
				TransferWinningCardsWithEmptyHands(false);

			}
			//if the player wins or the cards are equal (there is an underdog advantage to the computer who is about to lose),
			//	then continue playing the game
			else
			{
				//if the cards are the same... give advantage to underdog
				if (pTable.GetTop()->dataCard == cTable.GetTop()->dataCard)
				{
					//echo prompt that the player wins because cards are equal
					cout << endl << "Cards are equal... Advantage and win to player! Transferring winning cards..." << endl;
				}
				else
				{
					//echo prompt that the player wins
					cout << endl << "Player Wins! Transferring winning cards..." << endl;
				}

				//transfer winning cards to player
				TransferWinningCardsWithEmptyHands(true);

				//player still in the game, so push one card to the table so comparisons can continue
				pTable.Push(pCards.Pop());
				//set the continue flag to false
				continueFlag = true;
			}//if 
		}//if
		//if there is no cards on one or both tables, then automatically set the player to win and do not continue
		else
		{
			//set the boolean flag that the player won
			continueFlag = false;
			//set the boolean value that the computer has won
			computerWinner = true;
		}
	}
}

/*****************************************************************************************/
/* gameType PushCardsToTable - This function handles the game logic of pushing cards to the
* table for new rounds. The function is passed a continueFlag by reference to determine 
* whether or not new rounds can be played. In the event that the player/computer does not
* have enough cards in their hand, their winning pile is pushed to their hand. If both the
* computer/player's hand and winning cards are empty, the EmptyHandAndWinningCardLogic
* handles the game logic for sudden death card comparison for win/lose conditions. 
******************************************************************************************/
void gameType::PushCardsToTable(bool& continueFlag)
{
	//push a card from the computer card stack onto the players table stack
	if (!cCards.IsEmpty())
	{
		//push computers card to table from hand
		cTable.Push(cCards.Pop());
	}
	//push the winning cards from the COMPUTER to the COIMPUTERs hand stack
	else
	{
		//check to see if the computer's winning cards are empty...
		if (cWinCards.IsEmpty() && cCards.IsEmpty())
		{
			//handle the game logic when the computer runs out of cards 
			EmptyHandAndWinningCardLogic(continueFlag, true);
		}

		//while the computer has cards in their winning pile, add them to their hand
		else
		{
			//add cards to the computer hand while there are still cards in the winning
			//	pile
			while (!cWinCards.IsEmpty())
			{
				//add cards from the players winning card hand to their hand
				cCards.Push(cWinCards.Pop());
			}

			//push computers card to table from hand
			cTable.Push(cCards.Pop());
		}
	}

	//push a card from the players card stack onto the players table stack
	if (!pCards.IsEmpty())
	{
		//push players cards to table from hand
		pTable.Push(pCards.Pop());
	}
	//push the winning cards from the PLAYER to the PLAYERs hand stack
	else
	{
		//check to see if the player's winning cards are empty...
		if (pWinCards.IsEmpty() && pCards.IsEmpty())
		{
			//handle the game logic when the player runs out of cards 
			EmptyHandAndWinningCardLogic(continueFlag, false);
		}
		//while the player has cards in their winning pile, add them to their hand
		else
		{
			//while the player has cards in their winning pile, add them to their hand
			while (!pWinCards.IsEmpty())
			{
				//add cards from the players winning card hand to their hand
				pCards.Push(pWinCards.Pop());
			}

			//push players cards to table from hand
			pTable.Push(pCards.Pop());
		}
	}
}

/*****************************************************************************************/
/* gameType TransferWinningCards - This function transfers the winning card stacks to the 
* computer/player hands based on the boolean flag that is passed in. If the boolean flag
* is true, then handle transferring winning cards to player, if false, handle transferring
* winning cards to the computer. This function is used in EmptyHandAndWinningCardLogic,
* and thus instead of transferring winning cards to the winning stack, we transfer it to
* the player/computers hand because they have no cards in their hand. 
******************************************************************************************/
void gameType::TransferWinningCardsWithEmptyHands(bool computerOrPlayer)
{
	//true if transferring to player -- false if transferring to computer
	if (computerOrPlayer)
	{
		//while there is still cards on the computers table
		while (!cTable.IsEmpty())
		{
			//push the cards from the computers table to the players hand
			//because they have no cards
			pCards.Push(cTable.Pop());
		}

		//while there is still cards on the players table
		while (!pTable.IsEmpty())
		{
			//push the cards from the players table to the players hand
			pCards.Push(pTable.Pop());
		}
	}
	//transfer winning cards on the table to the computer
	else
	{
		//while there is still cards on the computers table
		while (!cTable.IsEmpty())
		{
			//push the cards from the computers table to the computer's hand because
			// their hand has no cards
			//cWinCards.Push(cTable.Pop());
			cCards.Push(cTable.Pop());
		}

		//while there is still cards on the players table
		while (!pTable.IsEmpty())
		{
			//push the cards from the players table to the computers hand
			//cWinCards.Push(pTable.Pop());
			cCards.Push(pTable.Pop());
		}
	}
}

/*****************************************************************************************/
/* gameType PrintComputersAndPlayersCards - This function prints the winning cards and counts
* of the players/computers stacks to the screen. 
******************************************************************************************/
void gameType::PrintComputersAndPlayersCards(void)
{
	//check that the player/computer tables have a card on them
	if (pTable.GetTop() != NULL && cTable.GetTop() != NULL)
	{
		//print the first half of the game screen for the computer with stack counts and 
		//	their winning stack
		PrintWinCardsAndStack(true);

		//show the computer's card
		cout << "Computer's Card: " << cTable.GetTop()->dataCard << endl << endl;
		//show the player's card
		cout << "Player's Card:   " << pTable.GetTop()->dataCard << endl;

		//print the second half of the game screen for the player with stack counts and 
		//	their winning stack
		PrintWinCardsAndStack(false);
	}
}

/*****************************************************************************************/
/* gameType War - This function handles the game logic when War occurs (when two players
* have the same card.) The function pushes 4 cards to the table, with only the last card
* being shown to the players. Then the cards are compared, and a winner determined. The 
* winner takes all the cards on both players tables. If at any point either player does 
* not have enough cards to continue war, PushCardsToTable handles pushing the player/computers
* winning cards to their hand. If they do not have enough cards to continue, then sudden 
* death occurs by comparing the last card. If the players have the same card after a round
* of war, the function calls War recursively by calling DoubleWarLogic. The boolean flag
* playNextRound is passed by reference. If any end conditions are met, the flag will 
* inhibit further rounds being played. 
******************************************************************************************/
void gameType::War(bool& playNextRound)
{
	//boolean variables for the refill logic and an index counter
	bool continueWar;
	int index;

	//set index to 0 and set continue to true
	index = 0;
	continueWar = true;

	//print war screen
	cout << "*******************************" << endl;
	cout << " ** !!   IT'S WAR THEN   !! ** " << endl;
	cout << "*******************************" << endl << endl;

	//push 4 cards from the computers/players hand to the table
	for (index = 0; index < 4; index++)
	{
		//take cards from the computer/player card stack and push them onto the table
		//	4 times -- Do not show these cards to the computer/player
		// Use the PushCardsToTable to handle edge cases when computer/player does not 
		//	have enough cards for war
		PushCardsToTable(continueWar);
	}	

	//based on the continueWar boolean flag, prints the cards necessary for war
	if (continueWar)
	{
		//prints 3 cards face down with the final card being shown to the players
		PrintWarCardsPreWar();
	}

	//if there is a second round of war... use short circuit comparison to make sure
	//	that war can continue based on the number of cards in the computers/players hands
	if (continueWar && cTable.GetTop()->dataCard == pTable.GetTop()->dataCard)
	{
		//handle the double war logic, which calls the War function recursively
		DoubleWarLogic(playNextRound);
	}
	//if there is no second time war, then show the winner and the cards
	else if (continueWar)
	{
		//check if the computer wins war
		if (cTable.GetTop()->dataCard > pTable.GetTop()->dataCard)
		{
			//print that computer wins war
			cout << endl << endl << "!! Computer Wins War !!" << endl << endl;

			//print the war results (includes the winning cards that were face down for 
			//	both players and transfer them to 
			PrintAndTransferWarCardsResults(false);

			//show that you are transferring to the computer's winning pile
			cout << endl << "Transferring to computer's winning pile..." << endl;
		}
		//player wins war
		else 
		{
			//print that player wins war
			cout << endl << endl << "!! Player Wins War !!" << endl << endl;

			//print the war results (includes the winning cards that were face down for 
			//	both players
			PrintAndTransferWarCardsResults(true);

			//show that you are transferring to the computer's winning pile
			cout << endl << endl << "Transferring to player's winning pile..." << endl;
		}
	}

	//divider from game title from the next round
	OutputDivider((ofstream&)cout, '=', SCREEN_SIZE);
}

/*****************************************************************************************/
/* gameType DoubleWarLogic - This function calls the War function recursively if both the 
* computer/player have cards in hand. If they do not, then whoever does not have any cards
* (only can be one or the other at any given time) then the respective player loses. If
* they have cards, then call War recursively. Use the boolean continueFlag to regulate
* whether or not the game continues based on end game conditions. 
******************************************************************************************/
void gameType::DoubleWarLogic(bool& continueFlag)
{
	//try to push/refill cards to the table again based on the boolean flag passed in
	PushCardsToTable(continueFlag);

	//check if either the computer or the computer does not have any cards
	if (cCards.GetCountOfCardsInStack() == 0 || pCards.GetCountOfCardsInStack() == 0)
	{
		//if the computer still does not have any cards in hand, the winner is the player
		if (cCards.GetCountOfCardsInStack() == 0)
		{
			//set winner/loser
			playerWinner = true;
			computerWinner = false;
		}
		//if the computer still does not have any cards in hand, the winner is the computer
		else if (pCards.GetCountOfCardsInStack() == 0)
		{
			//set winner/loser
			playerWinner = false;
			computerWinner = true;
		}
	}
	//if both players have cards, then war continues, print it for the user
	else
	{
		//show that war continues more than once
		cout << endl << "WAR Continues..." << endl << endl;

		//recursively call war
		War(continueFlag);
	}
}

/*****************************************************************************************/
/* gameType PrintWarCardsPreWar - This function prints 3 'upside down' character cards to 
* the screen and then reveals the final card from the computer/player to be pushed to the
* table.
******************************************************************************************/
void gameType::PrintWarCardsPreWar(void)
{
	//index counter
	int index;

	//show the computers WAR cards
	cout << "Computer's cards: ";

	//print 3 blank characters (they are upside down cards)
	for (index = 0; index < 3; index++) cout << setw(4) << "\u2589";
	//print the last card to be pushed to the table
	cout << cTable.GetTop()->dataCard << endl;

	//show the players WAR cards
	cout << endl << "Player's cards:   ";

	//print 3 blank characters (they are upside down cards)
	for (index = 0; index < 3; index++) cout << setw(4) << "\u2589";
	//print the last card to be pushed to the table
	cout << pTable.GetTop()->dataCard << endl;
}

/*****************************************************************************************/
/* gameType PrintAndTransferWarCardsResults - This function takes in the boolean flag 
* computerOrPlayer to determine where to send the winning cards after a round of war. 
* If the boolean flag is true, then send winning cards from the table to the player's 
* winning stack, and vice versa for the computer. Show the cards as they are popped from 
* the table for the players. 
******************************************************************************************/
void gameType::PrintAndTransferWarCardsResults(bool computerOrPlayer)
{
	//true if transferring winning cards to player -- false if transferring to computer
	if (computerOrPlayer)
	{
		//show the computer's war cards
		cout << "Computer's WAR cards: ";

		//while there is still cards on the computers table
		while (!cTable.IsEmpty())
		{
			//print the card on the table before being popped from the table
			cout << cTable.GetTop()->dataCard;
			//push the cards from the computers table to the players winning stack
			pWinCards.Push(cTable.Pop());
		}

		//show the player's war cards
		cout << endl << "Player's WAR cards:   ";

		//while there is still cards on the players table
		while (!pTable.IsEmpty())
		{
			//print the card on the table before being popped from the table
			cout << pTable.GetTop()->dataCard;
			//push the cards from the players table to the players winning stack
			pWinCards.Push(pTable.Pop());
		}
	}
	//transfer winning cards on the table to the computer
	else
	{
		//show the computer's war cards
		cout << "Computer's WAR cards: ";

		//while there is still cards on the computers table
		while (!cTable.IsEmpty())
		{
			//print the card on the table before being popped from the table
			cout << cTable.GetTop()->dataCard;
			//push the cards from the computers table to the players winning stack
			cWinCards.Push(cTable.Pop());
		}

		//show the player's war cards
		cout << endl << "Player's WAR cards:   ";

		//while there is still cards on the players table
		while (!pTable.IsEmpty())
		{
			//print the card on the table before being popped from the table
			cout << pTable.GetTop()->dataCard;
			//push the cards from the players table to the players winning stack
			cWinCards.Push(pTable.Pop());
		}
	}
}

/*****************************************************************************************/
/* gameType PlayRound - This function handles the main game logic for War by playing each
* round, and returning a boolean flag based on the playNextRound flag that is passed in. 
* This flag can be changed to false, depending on the PushCardsToTable and War functions
* that handle end of game logic. The function pushes two cards to the table, prints them,
* and compares them. Depending on the winner, the cards from the table are pushed to the
* winning players stack. If the playNextRound flag is set to false, do not continue
* playing rounds, and return a false flag to exit playing rounds. 
******************************************************************************************/
bool gameType::PlayRound(bool& playNextRound)
{
	//push one card from the player and the computer to the table, check to see they have cards
	//	in their hands or in their winning stacks -- handle logic if they do not have enough cards
	PushCardsToTable(playNextRound);

	//check if the player/computer have cards on the table, if they do not, set the playNextRound 
	//	flag to false, and do not continue game logic and return false flag
	if (playNextRound)
	{
		//print the player and computers winning stack, along with hand/stack counts
		PrintComputersAndPlayersCards();

		//check to see if the cards are the same
		if (pTable.GetTop()->dataCard == cTable.GetTop()->dataCard)
		{
			//if so, play war
			War(playNextRound);
		}

		//if players card is higher...
		//else if (playerTableCard->dataCard > computerTableCard->dataCard)
		else if (pTable.GetTop()->dataCard > cTable.GetTop()->dataCard)
		{
			//show that the player wins the round
			cout << "Player wins round!" << endl;

			//if the players card is larger then push the computer card, their card, to the players winning stack
			// playerTableCard + computerTableCard --> pWinCards
			pWinCards.Push(pTable.Pop());
			pWinCards.Push(cTable.Pop());
		}
		//if the computers card is higher...
		else
		{
			//show that the computer wins the round
			cout << "Computer wins round!" << endl;

			//if the computers card is larger then push the player card, their card, to the computers winning stack
			// playerTableCard + computerTableCard --> cWinCards
			cWinCards.Push(pTable.Pop());
			cWinCards.Push(cTable.Pop());
		}
	}

	//return the playNextRound flag
	return playNextRound;
}


/*****************************************************************************************/
/* gameType PrintWinCardsAndStack - This function prints the computers/players computers
* hand counts, winning card stack count, and the winning stack cards. The function takes
* in the computerOrPlayer boolean flag to determine whether printing for computer (true)
* or printing for player (false).
******************************************************************************************/
void gameType::PrintWinCardsAndStack(bool computerOrPlayer)
{
	//if printing for the computer, flag will be true
	if (computerOrPlayer)
	{
		//divider from game title
		OutputDivider((ofstream&)cout, '=', SCREEN_SIZE);

		//show how many cards the computer has left
		cout << setw(TAB) << "COMPUTER || Hand Cards left: " << cCards.GetCountOfCardsInStack() << endl;
		//show how many cards the computer has in their stack
		cout << setw(11) << right << "Winning Cards: " << cWinCards.GetCountOfCardsInStack() << endl;

		//show the computers winning card stack
		cout << "Computer's Winning stack => " << endl;
		//show stack
		cWinCards.ShowStack();
		//new lines 
		cout << endl << endl << endl;
	}
	else
	{
		//show how many cards the player has left
		cout << endl << endl << setw(TAB) << "PLAYER || Cards left: " << pCards.GetCountOfCardsInStack() << endl;
		//show how many cards the player has in their stack
		cout << setw(9) << right << "Winning Cards: " << pWinCards.GetCountOfCardsInStack() << endl;

		//show the players winning card stack
		cout << "Player's Winning Stack => " << endl;
		//show stack
		pWinCards.ShowStack();
		//new lines
		cout << endl << endl << endl;
		
		//print divider 
		OutputDivider((ofstream&)cout, '=', SCREEN_SIZE);
	}
}

/*****************************************************************************************/
/* gameType InGameUserMenu - This function prints a menu that is printed every round
* that gives the user at any time to step through the game, round by round, or to auto play
* the game, or exit the game. Perform error checking on the user's choice, and return
* their input selection. 
******************************************************************************************/
int gameType::InGameUserMenu(void)
{
	//selection variable for user
	int userSelection;

	//output divider
	OutputDivider((ofstream&)cout, '-', SCREEN_SIZE);

	//show menu for the user
	cout <<  "NEXT (1)" << " || " << setw(TAB) << "AUTO (2)" << " || " << setw(TAB)
		<< "EXIT (3) " << endl;
	//user selection arrow
	cout << " -> ";

	//get the user's selection
	cin >> userSelection;

	//perform error checking on the user's input if they do not make a correct selection
	while (userSelection != 1 && userSelection != 2 && userSelection != 3)
	{
		//print error message
		cout << endl << "Please input from the menu... valid inputs are 1, 2, or 3. " << endl;

		//get user's input again
		cin >> userSelection;
	}

	//return the user's selection
	return userSelection;
}

/*****************************************************************************************/
/* gameType Default Constructor - This destructor destroys the game class type
* and prints a message to the screen.
******************************************************************************************/
gameType::~gameType(void)
{
	//accumulator counter
	static int counter = 0;

	//echo prompt -- uncomment to see destructions of objects
	//cout << "Deck Class Object # " << ++counter << " destroyed. " << endl;
}