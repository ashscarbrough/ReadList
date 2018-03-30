/*************************************************************************

AUTHOR  : Ash Scarbrough and John Russo and some by Matt Holloway

SOURCE  :
with the help from shell program a9shell.cpp

DATE    : 4/21/2015

COMPILER: Microsoft Visual Studio 13 c++ .net

ACTION  : The program tests routines designed to perform various
operations on singly linked lists. The lists have a
dummy head node that holds the _ character. The tail of
the lists points to NULL.

This is an extended program of homework #8
The menu choices also all reading in a list from an
external file and sorting a list.

*************************************************************************/

/****************************   ReadList    *****************************

DESCRIPTION   Builds a singly linked list with a dummy head node. The
characters in the list are read in from an external file
in the same order in which they are found in file.

Input to list terminates when the End of File is encountered

PARAMETERS

IN, List    A pointer to a singly linked list with a dummy head node.
It is imperative that List be initialized before calling
this routine.

IN, FileName  A pointer to a string that has the name of the file to
open, if error in opening then return a 1;

RETURNS      1 if file opening error, 0 if read from file successful

NOTE          Before building the new list, ZapList is called. This
ensures that a memory leak does not develop.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int ReadList(NodePtr List, char FileName[])
{
	ifstream indata(FileName);              //Declare file variable to read from
	char NewChar;

	if (!indata)		//If read file fails;
		return 1;		//Return 1 if failure

	else
	{
		ZapList(List);                     //Make sure list is empty

		indata.get(NewChar);

		while (indata.good())
		{
			List->Link = new(nothrow)Node;	//Creates a new Node for List
			if (List->Link == NULL)		//Checks to see if there is enough memory
			{					//If not, Link will point to NULL
				cerr << "\nMemory allocation error for new list item";
				exit(1);
			}

			List = List->Link;		//Moves List to the next Node in sequence
			List->Ch = NewChar;		//Insert user provided character into next Node;
			List->Link = NULL;		//Initializes last pointer to NULL
			indata.get(NewChar);	//Obtains next char input from user
		}
	}
	return 0;
}


/**************************  SortList ************************************

Description  Arranges the singly linked list pointed to by List in
natural order.  It is assumed that the list has a dummy
head node.

The algorithm used is a linked variation of the selection
sort and works like this:
Start with EndSorted aimed at first node of list

repeat
Find smallest char between EndSorted and end of list
Swap smallest element with char in EndSorted
Change EndSorted to next node
until we get to end of list

None of the pointers in linked list are changed

Parameters
IN, List  A pointer to a singly linked list with a dummy head node
-----------------------------------------------------------------------*/
void SortList(NodePtr List)
{
	NodePtr SmallNode;        //points to smallest char
	NodePtr SearchNode;       //used to search each node in list
	NodePtr EndSorted;       //points to list to sort
	char TempCh;

	EndSorted = List->Link;	 //Set EndSorted to first Node after dummy head

	while (EndSorted->Link->Link != NULL)  //EndSorted will be moved up to
	{									  //second to last list item
		SmallNode = EndSorted;	 //EndSorted assumed smallest Node at start
		SearchNode = EndSorted->Link;

		while (SearchNode != NULL)	//Searches up through last Node
		{
			if (SmallNode->Ch > SearchNode->Ch)	 //If smallest list item is 
			{						 //larger than searched list item
				TempCh = SearchNode->Ch;
				SearchNode->Ch = SmallNode->Ch;	//Switch list items
				SmallNode->Ch = TempCh;		

				SearchNode = SearchNode->Link;	
			}

			else //If smallest Node remains smallest, advance SearchNode
			{
				SearchNode = SearchNode->Link;
			}
		}
		EndSorted = EndSorted->Link; //Once minimum number is found advance
	}					   //to next unsorted list location
}
