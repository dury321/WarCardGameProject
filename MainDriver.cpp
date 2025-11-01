//-------------------------------------------------------------------------------------------------
// Programmer: Christian Dury
// Program Flow (IPO):
//		Inputs:		Input from the keyboard. 
//		Outputs:	Output to computer screen.
//		Process:	The following program plays the game Russian variant of War. There are several objects: 
// cards, decks, stacks, and the game class, that interact to produce the game logic. There are several 
// stacks that hold the cards for game play: player/computer hand cards, player/computer winning 
// cards, and player/computer table stack.  Firstly, the program starts by prompting the user with 
// a start game menu that allows the user to start the game or to exit the game. If the user chooses
// to start the game, the game initializes by creating a deck of 52 cards. The cards are split 
// evenly between the computer and the player by distributing it to their respective hand card stacks.
// The computer and player then push cards from their hands to the table, where the cards are compared.
// The winner is determined by the player who has the higher card value (by rank). These winning 
// cards are pushed to the respective player’s winning card stacks. If both players have cards of the
// same rank, then War is played where 4 cards are pushed to each table (with only the 4th card visible)
// and this 4th card is compared between players. Whoever wins gets all the cards on the table. 
// Each player’s winning stacks are shown after each round. Play continues until a player/computer 
// runs out of cards, where then the winning stack of cards is pushed to the respective players hand. 
// he game continues until one player has won all of the cards. There is an in-game menu for the user 
// where they can choose to step through each round individually, or to auto play until there is a winner,
// or if the user wants to end the game at any time. 
// 
// There are several edge cases considered, most of them having to do with when a computer/player runs 
// out of cards in the midst of War. If one player runs out of cards during war, then Sudden Death occurs, 
// where the last two cards pushed to the table are compared, and the winner gets the cards on the table. 
// If the last cards are the same, there is an advantage to the underdog, or player who is about to lose. 
// They automatically win these cards. War is handled recursively. Theoretically, War can continue indefinitely,
// therefore there is a safety measure in place where only a set number of rounds can be played. 
//-------------------------------------------------------------------------------------------------

#include "OutputClass.h"
#include "CardClass.h"
#include "DeckClass.h"
#include "StackClass.h"
#include "GameClass.h"

int main(void)
{
	//initialize the war game class
	gameType warGames;

	//integer variables for user menu selection, and round counter
	int userGameStartMenuSelection;
	int userInGameMenuSelection;
	int roundCounter;

	//boolean variable to control next round logic
	bool nextRound;

	//initialize selections, counters, and flags
	roundCounter = 0;
	userGameStartMenuSelection = 0;
	userInGameMenuSelection = 0;
	nextRound = false;

	//set the userGameStartMenuSelection based on user selection from menu 
	//	screen
	userGameStartMenuSelection = warGames.MenuScreen();

	// --------------------------- Menu Selection --------------------------------
	//check if the user wants to end the game
	if (userGameStartMenuSelection == 2)
	{
		//echo prompt user is ending the game
		cout << endl << "Have a good day! " << endl;
		
		//end game
		return 0;
	}
	//if the user does not select to end the game, continue
	else
	{
		//start the game by shuffling deck, assigning player/computer stacks
		warGames.StartGame();
		//set to play the next round
		nextRound = true;

		//clear screen from the start game menu
		system("cls");
	}

	// --------------------------- Game Logic ------------------------------------
	//play the game
	do
	{
		//play a round, reset the next round based on the flag passed through
		nextRound = warGames.PlayRound(nextRound);

		//keep track of counter for user's computer safety... do not exceed
		//	maximum number of rounds allowed in case of potential infinite game
		roundCounter++;
		
		//get the in-game menu selection from the user
		userInGameMenuSelection = warGames.InGameUserMenu();

		//if the user selects to play the next round manually, clear the screen for
		//	clean input
		if (userInGameMenuSelection == 1)
		{
			//clear the screen
			system("cls");
		}

		//if the user selects auto play, continue playing rounds until there is a 
		//	winner determined
		if (userInGameMenuSelection == 2)
		{
			//continue playing the game while a winner is not determined
			while (!warGames.GetComputerWinner() && !warGames.GetPlayerWinner())
			{
				//set next round flag based on the round
				nextRound = warGames.PlayRound(nextRound);
			}
		}
		//if the user wants to end the game...
		else if (userInGameMenuSelection == 3)
		{
			//print dividers and echo prompt
			OutputDivider((ofstream&)cout, '-', SCREEN_SIZE);
			cout << endl << "EXITING GAME..." << endl << endl;
			OutputDivider((ofstream&)cout, '-', SCREEN_SIZE);

			//exit the game
			return 0;
		}

	//continue playing while next round is true, and we have not encountered the max
	//	number of rounds
	} while (nextRound && roundCounter < MAX_ROUNDS);	
	
	// --------------------------- Check Winner ----------------------------------
	//once the playNextRound while loop has exited, there is a winner condition
	//	check if the winner is the computer
	if (warGames.GetComputerWinner())
	{
		//print that the computer won, and a game over prompt
		cout << endl << endl << "*******************" << endl;
		cout << "** Computer Won! **" << endl;
		cout << "*******************" << endl << endl;
		cout << endl << " GAME OVER " << endl;

	}
	//check if the winner is the player is the player
	else if (warGames.GetPlayerWinner())
	{
		//print that the player won, and a game over prompt
		cout << endl << endl << "*******************" << endl;
		cout << "** Player Won! **" << endl;
		cout << "*******************" << endl << endl;
		cout << endl << " GAME OVER " << endl;
	}
	//if there is no winners, then the maximum number of rounds has been reached
	else
	{
		//echo prompt, and say that the game is a tie!
		cout << endl << " Maximum Rounds Encountered, it's a TIE! " << endl;
		cout << " GAME OVER " << endl;
	}
	
	//pause the game before exiting to see last winning round
	system("pause");
	
	//end program
	return 0;
}