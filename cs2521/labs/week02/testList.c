// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"

void indication (DLList mylist, char *it);

int main (void)
{	
	FILE *start = fopen("text", "r+");
	DLList myList = getDLList (start);
	putDLList (stdout, myList);
	assert (validDLList (myList));

	// Before + first node
	printf("\nInserting before the first node\n");
	indication(myList, "Before");
	DLListBefore(myList, "Before_first_node\n");
	indication(myList, "After");
	assert (validDLList (myList));
	// After + first node
	printf("\nInserting after the first node\n");
	indication(myList, "Before");
	DLListAfter(myList, "After_first_node\n");
	indication(myList, "After");
	assert (validDLList (myList));
	// After + last node
	DLListMoveTo(myList, (int)DLListLength(myList));
	printf("\nInserting after the last node\n");
	indication(myList, "Before");
	DLListAfter(myList, "After_last_node\n");
	indication(myList, "After");
	assert (validDLList (myList));
	// Before + last node
	printf("\nInserting before the last node\n");
	indication(myList, "Before");
	DLListBefore(myList, "Before_last_node\n");
	indication(myList, "After");
	assert (validDLList (myList));
	// show the state of the list before the operation (including curr and nitems)
	
	// indicate what operation is about to be performed
	printf("\nRun till all the node is deleted (cover all the cases except the last one)\n");
	// invoke the operation
	for (int count = (int)DLListLength(myList); count > 0; count--) {
		indication(myList, "Before");
		DLListDelete(myList);
		indication(myList, "After");
		assert (validDLList (myList));
	}
	// Deleting a NULL list
	printf("\nDeleting a Null list\n");
	indication(myList, "Before");
	DLListDelete(myList);
	indication(myList, "After");
	assert (validDLList (myList));
	// Inserting the node in a NULL list
	// display the state of the list after the operation
	// run the validDLList() check on the list
	printf("\nInserting the node in a NULL list\n");
	DLListAfter(myList, "After\n");
	printf("nitems: %zu\n", DLListLength(myList));
	printf("curr: %s\n", DLListCurrent(myList));
	assert (validDLList (myList));
	// Deleting the node
	printf("Deleting the last node\n");
	DLListDelete(myList);
	printf("nitems: %zu\n", DLListLength(myList));
	printf("curr: %s\n", DLListCurrent(myList));
	assert (validDLList (myList));
	// Inserting before in a NULL list
	printf("\nInserting the node in a NULL list\n");
	indication(myList, "Before");
	DLListBefore(myList, "Before\n");
	indication(myList, "Before");
	assert (validDLList (myList));
	// Inserting before in a list with only one node
	printf("\nInserting the node in a one node list\n");
	indication(myList, "Before");
	DLListBefore(myList, "Before_2\n");
	indication(myList, "Before");
	assert (validDLList (myList));
	// Deleting the first node
	printf("Deleting the first node\n");
	printf("=========Before========\n");
	printf("nitems: %zu\n", DLListLength(myList));
	printf("curr: %s", DLListCurrent(myList));
	DLListDelete(myList);
	indication(myList, "Before");
	assert (validDLList (myList));
	// Inserting after in a list with only one node
	printf("Inserting after in a list with only one node\n");
	printf("=========Before========\n");
	printf("nitems: %zu\n", DLListLength(myList));
	printf("curr: %s", DLListCurrent(myList));
	DLListAfter(myList, "After_1");
	indication(myList, "Before");
	assert (validDLList (myList));

	// TODO: more tests needed here

	freeDLList (myList);
	return EXIT_SUCCESS;
}

void indication (DLList myList, char *it) {
	printf("=========%s========\n", it);
	printf("nitems: %zu\n", DLListLength(myList));
	printf("curr: %s\n", DLListCurrent(myList));
}
