//--------------------------------------------------------------------------------------------------
//File Name:        StackClass.cpp
//Associated File:  StackClass.h
//Contains:
//  Constructors:	Default:	stackType					
//  Access:
//   Get -						GetTop, GetNode	
//   Set -						None	
//   Print -					ShowStack	
//								
// Other Methods -				IsEmpty, FreeStack, Push, Pop
// Destructor: 
//			Default:			~stackType
//--------------------------------------------------------------------------------------------------

#include "StackClass.h"

/*****************************************************************************************/
/* stackType Default Constructor - The default constructor calls CreateAStack to create 
* a stack of 52 nodes that consists of the card object and the node pointer. 
******************************************************************************************/
stackType::stackType(void)
{
	//object creation counter
	static int counter = 0;

	//echo prompt -- uncomment to see initializations of objects -- uncomment to see object creation
	//cout << "Stack Class Object # " << ++counter << " created. " << endl;

	//create a stack and set the top pointer to NULL
	CreateAStack();

	//set tag field to 0
	countOfCardsInStack = 0;

}

/*****************************************************************************************/
/* stackType GetANode - This function returns the node pointer for the card type object
* that is passed into the function. This function creates a new node, assigns the pointer
* for the data card for the card object that is passed in, and sets the linking pointer 
* to NULL. 
******************************************************************************************/
nodePtr stackType::GetANode(cardType aCard)
{
	//create a node, and set the pointer to the address of this node
	nodePtr pointer = new node;

	//assign the card passed in to the data in the node
	pointer->dataCard = aCard;

	//assign pointer a value, set the pointer of new node to NULL
	pointer->link = NULL;

	//return the pointer
	return pointer;
}

/*****************************************************************************************/
/* stackType Push - This function takes in a card object and calls the GetANode function to 
* create a new node for the card object. It sets the pointers to the new top of the stack,
* and the old top of the stack. The function increments the count of the number of cards
* in the stack. 
******************************************************************************************/
void stackType::Push(cardType aCard)
{
	//new node to store card data in
	nodePtr temp = GetANode(aCard);

	//point the new node link to the old top of the stack
	temp->link = top;

	// point top to the new top of the stack
	top = temp;

	//increment the tag field for the number of cards in the stack
	countOfCardsInStack++;
}

/*****************************************************************************************/
/* stackType Pop - This function returns a card object by 'popping' it from the stack. 
* If the stack is not empty, assign the data for the card object based on the stack object
* that is at the top of the stack. Assign the new node, the linking pointer, and then delete
* the temporary node pointer. If the stack is empty, print an error. Return the card object.
******************************************************************************************/
cardType stackType::Pop(void)
{
	//card object to hold the data for the card
	cardType data;

	//node pointer for assignment to the top of the stack
	nodePtr aNode;

	//check to see if the stack is empty
	if (!IsEmpty())
	{
		//assign data to the card that is on the top of the stack
		data = top->dataCard;

		aNode = top;	//keep track of where you have been -- point to the old top

		top = aNode->link;	// point to the next new top of the stack

		delete aNode;	// delete the old top node

		//decrease the number of items in the list by 1
		countOfCardsInStack--;
	}
	//if the stack is empty, send an error message that you are trying to 
	//	access an empty stack
	else
	{
		//error trying to pop from an empty stack
		cout << "Error: Cannot pop from an empty stack. " << endl;
	}

	//return the card type object
	return data;
}

/*****************************************************************************************/
/* stackType ShowStack - This function starts at the top of the stack, and prints all of the
* card type objects that are in the stack while the current pointer is not pointing to NULL
* (end of the stack.) 
******************************************************************************************/
void stackType::ShowStack(void)
{
	//node pointer for the top of the stack and an index for how many elements have been 
	//	printed for nicer printing
	nodePtr current;
	int index;

	//set the current index to the top of the stack -- set the index to 0
	current = top;
	index = 0;

	//while we are not at the end of the stack...
	while (current != NULL)
	{
		//print out the card that is found at the stack position
		cout << current->dataCard;

		//assign the new current based on the nodes link
		current = current->link;

		//increment the index
		index++;

		//if the index is equal to 10, then add a new line for nice printing
		if (index == 10)
		{
			//newline and reset index to 0
			cout << endl;
			index = 0;
		}
	}
}

/*****************************************************************************************/
/* stackType FreeStack - Frees the memory for all the nodes remaining in the linked
* list. The function iterates through the linked list and sets the links to NULL and deletes
* the nodes. It also decrements the count for the number of items in the list.
******************************************************************************************/
void stackType::FreeStack(void)
{
	//temporary node pointer
	nodePtr aNode;

	//while there are nodes in the linked list
	while (!IsEmpty())
	{
		//assign aNode to a value -- set the node to the first item in the list
		aNode = top;

		//this change in the value of start is because the node that was start will
		// be deleted and freed

		//assign start to a value - move start to the next node 
		top = top->link;

		//assign aNode's link a value -- sever pointer from the list
		aNode->link = NULL;

		//free the memory for this pointer
		delete aNode;
	}
}

/*****************************************************************************************/
/* stackType Default Destructor - This destructor destroys the stack class type
* and prints a message to the screen. Call free the stack to delete pointer and free memory.
******************************************************************************************/
stackType::~stackType(void)
{
	//accumulator counter
	static int counter = 0;

	//echo prompt -- uncomment to see destructions of objects
	//cout << "Stack Class Object # " << ++counter << " destroyed. " << endl;
	
	//free the stack and destroy the pointer and free the memory
	FreeStack();
}