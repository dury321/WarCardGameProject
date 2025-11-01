//--------------------------------------------------------------------------------------------------
//File Name:        StackClass.h
//Associated File:  StackClass.cpp
//Contains:
//  Constructors:	Default:	stackType
//	Members:					nodePtr: top
//								Integer: countOfCardsInStack
//  Access	
//   Get -	(inline)			GetCountOfCardsInStack
//			(defined in .cpp)	GetTop, GetNode
//   Set -	(inline)			None
//			(defined in .cpp)	None
//   Print -(inline)			None
//			(defined in .cpp)	ShowStack
//								
// Other Methods -				IsEmpty, FreeStack, Push, Pop
// Destructor: 
//			Default:			~stackType
//--------------------------------------------------------------------------------------------------

#pragma once
#include "DeckClass.h"

// node structure that holds a card object and the link pointing to the 
//	next element in the stack
struct node
{
	//card object for the data
	cardType dataCard;

	//pointer for the link to the next node
	node* link;
};

//create a type definition, which is a pointer to the node
typedef node* nodePtr;

//the stack type inherits from the deckType object
class stackType : public deckType
{
private:

	//private variables
	nodePtr top;

	//tag field for the number of cards in the stack
	int countOfCardsInStack;

	//create a stack by setting the top pointer to NULL (top of the stack)
	void CreateAStack(void) { top = NULL; }

public:

	// --------- Constructor ---------------
	//default constructor -- creates a stack and sets the top to NULL
	stackType(void);

	// --------- Public Methods -------------
	//get the count of the cards in the stack
	int GetCountOfCardsInStack(void) { return countOfCardsInStack; }

	//get the top card in the stack
	nodePtr GetTop(void) { return top; }
	
	//create and allocate memory for a node, fill it with a card
	nodePtr GetANode(cardType aCard);

	//returns a bool value of true if the list is empty, otherwise returns false
	bool IsEmpty(void) { return top == NULL; }

	//free the stack and delete pointers and data
	void FreeStack(void);
	
	//push a card onto the top of the stack
	void Push(cardType aCard);

	//pop a card from the top of the stack
	cardType Pop(void);

	// --------- Print Methods -------------
	//iterate through the stack and show the card at each place in the stack
	void ShowStack(void);

	// --------- Destructor ----------------
	//default destructor -- call free the stack to delete pointers and data
	~stackType(void);
	
};
